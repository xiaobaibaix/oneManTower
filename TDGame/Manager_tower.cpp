#include "Manager_tower.h"
#include "Manager_config.h"
#include "Tower_archer.h"
#include "Tower_axeman.h"
#include "Tower_gunner.h"
#include "Manager_config.h"
#include "Manager_game.h"


Manager_tower::Manager_tower()
{
	tile_map = &(Manager_config::instance()->map.get_tile_map());
}

void Manager_tower::on_update(double delta_time)
{
	const int& cur_coin_count = Manager_game::instance()->get_coin_count();
	for (Tower*& tower:tower_list) {
		tower->on_update(delta_time);
	}

	static Manager_ui* ui = Manager_ui::instance();
	if (!ui->is_mouse_right_down) {
		if (ui->is_select_top)generate_tower(ui->mouse_idx_pos_locked, TowerType::axeman);
		if (ui->is_select_right)generate_tower(ui->mouse_idx_pos_locked, TowerType::gunner);
		if (ui->is_select_left) generate_tower(ui->mouse_idx_pos_locked, TowerType::archer);
	}

	if (ui->is_mouse_double_down) {//升级
		update_tower(ui->mouse_idx_pos);
		ui->is_mouse_double_down = false;
	}
}

void Manager_tower::on_draw(SDL_Renderer* render)
{
	for (Tower*& tower:tower_list) {
		tower->on_draw(render);
	}
}

bool Manager_tower::generate_tower(const Vector2D& pos, TowerType type)
{
	const int idx_x = pos.x;
	const int idx_y = pos.y;

	//金币是否可以建造
	static Manager_game* game = Manager_game::instance();
	static Manager_config* config = Manager_config::instance();

	static const int& cost_cion = game->get_coin_count();

	switch (type)
	{
	case TowerType::invalid:
		break;
	case TowerType::archer:
		if (cost_cion < config->archer_template.cost[0])return false;
		break;
	case TowerType::axeman:
		if (cost_cion < config->axeman_template.cost[0])return false;
		break;
	case TowerType::gunner:
		if (cost_cion < config->gunner_template.cost[0])return false;
		break;
	default:
		break;
	}

	static const int buff_tile[] = {0,2,14,15,16,17,20,21,22,30,31,32};//可以放的地形下标
	int i = 0;
	for (; i < sizeof(buff_tile); i++) {
		if (tile_map->at(idx_y).at(idx_x).terrain == buff_tile[i]&& tile_map->at(idx_y).at(idx_x).decoration<0) {//地形可以放而且没有装饰
			if (tile_map->at(idx_y).at(idx_x).has_tower) {
				return false;
			}
			tile_map->at(idx_y).at(idx_x).has_tower = true;
			break;
		}
	}
	if (i == sizeof(buff_tile))return false;//地形不属于列表其内不能生成塔，返回

	switch (type)
	{
	case TowerType::archer:
		tower_list.push_back(new Tower_archer(idx_x,idx_y));
		game->dec_coin(config->archer_template.cost[0]);
		break;
	case TowerType::axeman:
		tower_list.push_back(new Tower_axeman(idx_x, idx_y));
		game->dec_coin(config->axeman_template.cost[0]);
		break;
	case TowerType::gunner:
		tower_list.push_back(new Tower_gunner(idx_x, idx_y));
		game->dec_coin(config->gunner_template.cost[0]);
		break;
	default:
		return false;
	}

	return true;
}

//传入像素坐标
bool Manager_tower::update_tower(const Vector2D& pos)
{
	static TileMap&tilemap=Manager_config::instance()->map.get_tile_map();
	if (!tilemap[pos.y][pos.x].has_tower)return false;
	int cur_coin_count = Manager_game::instance()->get_coin_count();

	for (auto& tower:tower_list) {
		if (tower->pos.x==pos.x&&tower->pos.y==pos.y) {
			int need_cost_coin = tower->upgrade_cost[tower->idx_grade];
			if (cur_coin_count < need_cost_coin)return false;
			Manager_game::instance()->dec_coin(need_cost_coin);
			return tower->addGrade();
		}
	}
	return false;
}

bool Manager_tower::update_tower(int idx_pos)
{

	return false;
}

void Manager_tower::delete_all_tower()
{

}

void Manager_tower::delete_tower()
{
}

const std::vector<Tower*>& Manager_tower::getTowerList() const
{
	return tower_list;
}


