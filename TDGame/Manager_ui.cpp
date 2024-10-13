#include "Manager_ui.h"
#include "Manager_resources.h"
#include "Manager_config.h"
#include "Manager_tower.h"
#include "Manager_game.h"

#include "Tile.h"

void Manager_ui::on_input(const SDL_Event* event)
{
	switch (event->type) {
	case SDL_MOUSEMOTION://Êó±êÒÆ¶¯
		mouse_pos = { (float)event ->motion.x,(float)event->motion.y };
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT) {
			static Uint32 last_click_time = 0;
			static const int mouse_double_time = 250;//ºÁÃë
			const Vector2D cur_mouse_pos = { (float)event->motion.x,(float)event->motion.y };
			const Uint32 current_time = SDL_GetTicks();
			//std::cout << current_time - last_click_time << std::endl;
			if (current_time- last_click_time< mouse_double_time&& mouse_pos== cur_mouse_pos) {
				is_mouse_double_down = true;
			}
			last_click_time = current_time;

			is_mouse_left_down = true;
			tmp_pos = { (float)(int)(cur_mouse_pos / SIZE_TILE).x,(float)(int)(cur_mouse_pos / SIZE_TILE).y };
		}
		if (event->button.button == SDL_BUTTON_RIGHT) {
			is_mouse_right_down = true;
		}
		break;
	case SDL_MOUSEBUTTONUP:
		if (event->button.button == SDL_BUTTON_LEFT) {
			//is_mouse_left_down = false;
		}
		if (event->button.button == SDL_BUTTON_RIGHT) {
			is_mouse_right_down = false;
		}
		break;
	default:
		break;
	}
}

void Manager_ui::on_update(double delta_time)
{
	mouse_idx_pos = { (float)(int)(mouse_pos.x / SIZE_TILE),(float)(int)(mouse_pos.y / SIZE_TILE) };
	
	if (!is_mouse_right_down) {
		mouse_idx_pos_locked = mouse_idx_pos;
		is_select_top = false;
		is_select_left = false;
		is_select_right = false;
	}
	//if(canLoseCoin)
}

void Manager_ui::on_draw(SDL_Renderer* render)
{
	//»­ÍßÆ¬Ñ¡Ôñ¿ò
	static SDL_Texture* tex=Manager_resources::instance()->get_texture_pool().find(ResID::Tex_UISelectCursor)->second;
	SDL_Rect rect_tex_curser = { mouse_idx_pos_locked.x*SIZE_TILE,mouse_idx_pos_locked.y*SIZE_TILE,SIZE_TILE,SIZE_TILE };
	SDL_RenderCopy(render, tex, nullptr, &rect_tex_curser);

	static Manager_config* config = Manager_config::instance();

	//»­¹¥»÷·¶Î§
	static auto& arther_view = config->archer_template.view_range[0];
	static auto& axeman_view = config->axeman_template.view_range[0];
	static auto& gunner_view = config->gunner_template.view_range[0];

	static TTF_Font* font = Manager_resources::instance()->get_font_pool().find(ResID::Font_Main)->second;
	static const int& coin_count = Manager_game::instance()->get_coin_count();
	static const int& home_hp = Manager_game::instance()->get_home_hp();

	//»­½¨ÔìËþµÄÑ¡Ïî¿ò
	if (is_mouse_right_down&&!config->map.get_tile_map().at(mouse_idx_pos_locked.y).at(mouse_idx_pos_locked.x).has_tower) {
		static SDL_Texture* tex_place_idle = Manager_resources::instance()->get_texture_pool().find(ResID::Tex_UIPlaceIdle)->second;
		static SDL_Texture* tex_place_left = Manager_resources::instance()->get_texture_pool().find(ResID::Tex_UIPlaceHoveredLeft)->second;
		static SDL_Texture* tex_place_top = Manager_resources::instance()->get_texture_pool().find(ResID::Tex_UIPlaceHoveredTop)->second;
		static SDL_Texture* tex_place_right = Manager_resources::instance()->get_texture_pool().find(ResID::Tex_UIPlaceHoveredRight)->second;

		Vector2D pos_center_locked = { mouse_idx_pos_locked.x* SIZE_TILE + SIZE_TILE / 2,mouse_idx_pos_locked.y* SIZE_TILE + SIZE_TILE / 2 };
		Vector2D distence = mouse_pos - pos_center_locked;

		int w, h;
		SDL_QueryTexture(tex_place_idle, nullptr,nullptr,&w, &h);

		SDL_Rect place_rect_dst = { pos_center_locked.x - w / 2,pos_center_locked.y - h / 2 ,w,h };

		if (distence.getMode_length()>SIZE_TILE/3) {
			double radians = atan2(distence.y, distence.x);
			double degrees = -radians * (180.0 / M_PI);
			//¾²Ì¬µÄÎÄ±¾×ÊÔ´
			static std::string text_str_archer = std::to_string((int)config->archer_template.cost[0]);
			static std::string text_str_axeman = std::to_string((int)config->axeman_template.cost[0]);
			static std::string text_str_gunner = std::to_string((int)config->gunner_template.cost[0]);
			static const char* text_built[] = {
				text_str_archer.c_str(),
				text_str_axeman.c_str(),
				text_str_gunner.c_str(),
			};

			static SDL_Color color_built = { 255, 100, 100 }; // °×É«

			static SDL_Surface* textSurface_archer = TTF_RenderText_Solid(font, text_built[0], color_built);
			static SDL_Surface* textSurface_axeman = TTF_RenderText_Solid(font, text_built[1], color_built);
			static SDL_Surface* textSurface_gunner = TTF_RenderText_Solid(font, text_built[2], color_built);

			static SDL_Texture* texture_archer = SDL_CreateTextureFromSurface(render, textSurface_archer);
			static SDL_Texture* texture_axeman = SDL_CreateTextureFromSurface(render, textSurface_axeman);
			static SDL_Texture* texture_gunner = SDL_CreateTextureFromSurface(render, textSurface_gunner);

			SDL_Rect rect_built = { pos_center_locked.x-20,pos_center_locked.y+50,40,30};

			if (degrees > 30 && degrees <= 150) {//¸«Í·
				SDL_RenderCopy(render, tex_place_top, nullptr, &place_rect_dst);
				filledCircleRGBA(render, pos_center_locked.x, pos_center_locked.y, axeman_view * SIZE_TILE, 50, 75, 0xda, 40);
				SDL_RenderCopy(render, texture_axeman, nullptr, &rect_built);
				is_select_top = true;
			}
			else if (degrees <= 30 && degrees > -90) {//ÅÚÊÖ
				SDL_RenderCopy(render, tex_place_right, nullptr, &place_rect_dst);
				filledCircleRGBA(render, pos_center_locked.x, pos_center_locked.y, gunner_view * SIZE_TILE, 50, 75, 0xda, 40);
				SDL_RenderCopy(render, texture_gunner, nullptr, &rect_built);
				is_select_right = true;
			}
			else {//¹­¼ý
				SDL_RenderCopy(render, tex_place_left, nullptr, &place_rect_dst);
				filledCircleRGBA(render, pos_center_locked.x, pos_center_locked.y, arther_view * SIZE_TILE, 50, 75, 0xda, 40);
				SDL_RenderCopy(render, texture_archer, nullptr, &rect_built);
				is_select_left = true;
			}
		}
		else {
			SDL_RenderCopy(render, tex_place_idle, nullptr, &place_rect_dst);
			is_select_top = false;
			is_select_left = false;
			is_select_right = false;
		}
	}
	//×ó¼üµã»÷ÏÔÊ¾¹¥»÷·¶Î§
	if (is_mouse_left_down) {
		if (config->map.get_tile_map().at(tmp_pos.y).at(tmp_pos.x).has_tower) {
			auto& tower_list=Manager_tower::instance()->getTowerList();
			for (auto& tower : tower_list) {
				if (tower->getPos().x== tmp_pos.x&&tower->getPos().y==tmp_pos.y) {
					filledCircleRGBA(render, tmp_pos.x*SIZE_TILE+SIZE_TILE/2, tmp_pos.y*SIZE_TILE + SIZE_TILE / 2, tower->getViewRange()* SIZE_TILE, 10,75, 0xda, 20);
				}
			}
		}
		else {
			is_mouse_left_down = false;
		}
	}

	//»æÖÆ
	std::string text_str = std::to_string(coin_count);
	const char* text = text_str.c_str();
	SDL_Color color = { 10, 10, 10 }; // °×É«
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text,color);
	SDL_Rect textRect = { 100, 40, textSurface->w, 22 };
	SDL_Texture* texture = SDL_CreateTextureFromSurface(render, textSurface);
	SDL_RenderCopy(render, texture, nullptr, &textRect);

	static SDL_Texture* tex_coin=Manager_resources::instance()->get_texture_pool().find(ResID::Tex_Coin)->second;
	static SDL_Texture* tex_home = Manager_resources::instance()->get_texture_pool().find(ResID::Tex_UIHomeAvatar)->second;
	static SDL_Texture* tex_player = Manager_resources::instance()->get_texture_pool().find(ResID::Tex_UIPlayerAvatar)->second;
	static SDL_Texture* tex_heart = Manager_resources::instance()->get_texture_pool().find(ResID::Tex_UIHeart)->second;

	static SDL_Rect rect_home_dst = { 5,5,60,60 };
	static SDL_Rect rect_coin_dst = {70,40,22,22};
	static SDL_Rect rect_hearts_dst = { 70,7,22,22 };

	SDL_RenderCopy(render, tex_home, nullptr, &rect_home_dst);
	SDL_RenderCopy(render, tex_coin, nullptr, &rect_coin_dst);
	for (int i = 0; i < home_hp; i++) {
		SDL_Rect rect_hearts_dst_ = { rect_hearts_dst.x + 30 * i,rect_hearts_dst.y,rect_hearts_dst.w,rect_hearts_dst.h };
		SDL_RenderCopy(render, tex_heart, nullptr, &rect_hearts_dst_);
	}
}

void Manager_ui::canLoseCoin(const Vector2D& pos)
{

	can_lose_coin = true;
}
