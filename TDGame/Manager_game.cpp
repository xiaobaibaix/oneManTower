#include "Manager_game.h"

#include <cmath>

int Manager_game::run(int argc, char** argv) {

	Uint64 last_counter = SDL_GetPerformanceCounter();
	const Uint64 counter_fre = SDL_GetPerformanceFrequency();
	while (!is_quit)
	{
		while (SDL_PollEvent(&event)) {
			on_input(&event);
		}
		const Uint64 cur_counter = SDL_GetPerformanceCounter();
		const double delta_time = (double)(cur_counter - last_counter) / counter_fre;
		last_counter = cur_counter;
		if (delta_time * 1000 < 1000.0f / FPS) {
			SDL_Delay((Uint32)(1000.0 / FPS - delta_time * 1000));
		}
		on_update(delta_time);

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		on_draw();

		SDL_RenderPresent(renderer);

	}
	return 0;
}

const int& Manager_game::get_coin_count()const
{
	return cur_coin_count;
}

const int& Manager_game::get_home_hp() const
{
	return cur_home_hp;
}

void Manager_game::add_coin(int coins)
{
	cur_coin_count += coins;
}

void Manager_game::dec_coin(int coins)
{
	cur_coin_count -= coins;
}

void Manager_game::dec_home_hp()
{
	cur_home_hp--;
}

Manager_game::Manager_game() 
{
	init_assert(!SDL_Init(SDL_INIT_EVERYTHING), u8"SDL 初始化失败");
	init_assert(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG), u8"IMG 初始化失败");
	init_assert(Mix_Init(MIX_INIT_MP3), u8"Mix 初始化失败");
	init_assert(!TTF_Init(), u8"TTF 初始化失败");

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");

	manager_config = Manager_config::instance();//配置管理器
	init_assert(manager_config->map.load("./fileData/map1.csv"), u8"加载游戏地图失败!");
	init_assert(manager_config->load_level_config("./fileData/level.json"), u8"加载关卡配置失败!");
	init_assert(manager_config->laod_game_config("./fileData/config.json"), u8"加载游戏配置失败!");

	window = SDL_CreateWindow(manager_config->basic_template.window_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,manager_config->basic_template.window_width, manager_config->basic_template.window_height, SDL_WINDOW_SHOWN);
	init_assert(window, u8"创建窗口失败");
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
	init_assert(renderer, u8"创建渲染器失败");

	manager_resources = Manager_resources::instance();//资源管理器
	init_assert(manager_resources->load_from_file(renderer),u8"加载资源失败!");

	init_assert(generate_tile_map_texture(), u8"生成纹理失败");//生成关卡地图纹理

	manager_wave = Manager_wave::instance();//波次管理去器
	manager_enemy = Manager_enemy::instance();//敌人对象管理器
	manager_tower = Manager_tower::instance();//防御塔对象管理器
	manager_ui = Manager_ui::instance();//ui管理器

}

Manager_game::~Manager_game() {

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	TTF_Quit();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

void Manager_game::init_assert(bool flag, const char* text) {
	if (flag)return;
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, u8"游戏启动失败!", text, window);
}

bool Manager_game::generate_tile_map_texture()
{
	Map& map = manager_config->map;
	TileMap& tile_map = map.get_tile_map();
	SDL_Rect& rect_tile_map = manager_config->rect_tile_map;
	SDL_Texture* tex_tile_set = manager_resources->get_texture_pool().find(ResID::Tex_Tileset)->second;

	int width_tex_tile_set=0, height_tex_tile_set=0;
	SDL_QueryTexture(tex_tile_set, nullptr, nullptr, &width_tex_tile_set, &height_tex_tile_set);

	int num_tile_single_line = (int)std::ceil((double)width_tex_tile_set / SIZE_TILE);

	int width_tex_tile_map, height_tex_tile_map;
	width_tex_tile_map = (int)map.get_width() * SIZE_TILE;
	height_tex_tile_map = (int)map.get_Height() * SIZE_TILE;

	tex_tile_map = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_TARGET, width_tex_tile_map, height_tex_tile_map);
	if (!tex_tile_map)return false;

	rect_tile_map.x = (manager_config->basic_template.window_width - width_tex_tile_map) / 2;
	rect_tile_map.y = (manager_config->basic_template.window_height - height_tex_tile_map) / 2;
	rect_tile_map.w = width_tex_tile_map;
	rect_tile_map.h = height_tex_tile_map;

	SDL_SetTextureBlendMode(tex_tile_map, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(renderer, tex_tile_map);

	for (int y = 0; y < map.get_Height();y++) {
		for (int x = 0; x < map.get_width();x++) {
			SDL_Rect rect_src;
			const Tile& tile = tile_map[y][x];

			const SDL_Rect& rect_dst = {
				x * SIZE_TILE,y * SIZE_TILE,SIZE_TILE,SIZE_TILE
			};

			rect_src = {
				(tile.terrain % num_tile_single_line) * SIZE_TILE,
				(tile.terrain / num_tile_single_line) * SIZE_TILE,
				SIZE_TILE,SIZE_TILE
			};
			SDL_RenderCopy(renderer, tex_tile_set, &rect_src, &rect_dst);
			if (tile.decoration >= 0) {
				rect_src = {
				(tile.decoration % num_tile_single_line) * SIZE_TILE,
				(tile.decoration / num_tile_single_line) * SIZE_TILE,
				SIZE_TILE,SIZE_TILE
				};
				SDL_RenderCopy(renderer, tex_tile_set, &rect_src, &rect_dst);
			}
		}
	}

	const SDL_Point& idx_home = manager_config->map.get_home_pos();
	const SDL_Rect& rect_dst = {
		idx_home.x * SIZE_TILE,idx_home.y * SIZE_TILE,
		SIZE_TILE,SIZE_TILE
	};

	SDL_RenderCopy(renderer, manager_resources->get_texture_pool().find(ResID::Tex_Home)->second, nullptr, &rect_dst);
	SDL_SetRenderTarget(renderer,nullptr);

	return true;
}

void Manager_game::on_input(const SDL_Event* event) {
	switch (event->type) {
	case SDL_QUIT://程序退出
		is_quit = true;
		break;

	case SDL_KEYDOWN:
		if (event->key.keysym.sym == SDLK_TAB) {
			// Tab键被按下
			is_debug = !is_debug;
		}
		break;
	default:
		break;
	}
	manager_ui->on_input(event);
}

void Manager_game::on_update(double delta_time) {
	static bool once = false;
	if (!once) {
		manager_wave->set_wave_list(&(manager_config->wave_list));
		once = true;
	}

	manager_wave->on_update(delta_time);
	manager_enemy->on_update(delta_time);
	manager_tower->on_update(delta_time);
	manager_ui->on_update(delta_time);

	//std::cout << "coin: " << cur_coin_count << std::endl;
}

void Manager_game::on_draw() {
	static const SDL_Rect& rect_dst = manager_config->rect_tile_map;

	SDL_RenderCopy(renderer, tex_tile_map, nullptr, &rect_dst);
	manager_enemy->on_draw(renderer);
	manager_tower->on_draw(renderer);
	manager_ui->on_draw(renderer);

}
