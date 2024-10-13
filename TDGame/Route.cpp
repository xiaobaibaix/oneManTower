#include "Route.h"

Route::Route(const TileMap& map, const SDL_Point& pos) {

	const size_t width_map = map.at(0).size();
	const size_t height_map = map.size();

	SDL_Point idx_nex = pos;

	while (true)
	{
		if (idx_nex.x >= width_map || idx_nex.y >= height_map)
			break;

		if (check_duplicate_idx(idx_nex))//Ñ­»·
			break;
		else {
			idx_list.push_back(idx_nex);
		}

		bool is_next_point_exist = true;
		const Tile& tile = map[idx_nex.y][idx_nex.x];

		if (tile.speical_flag == 0)//·¿ÎÝ
			break;
		else {
			switch (tile.direction)
			{
			case Tile::Direction::Up:
				idx_nex.y--;
				break;
			case Tile::Direction::Down:
				idx_nex.y++;
				break;
			case Tile::Direction::Left:
				idx_nex.x--;
				break;
			case Tile::Direction::Right:
				idx_nex.x++;
				break;
			default:
				is_next_point_exist = false;
				break;
			}
		}
		if (!is_next_point_exist)break;
	}

}

const Route::IdxList& Route::get_idx_list() {
	return idx_list;
}

bool Route::check_duplicate_idx(const SDL_Point& pos) {
	for (const SDL_Point& idx : idx_list) {
		if (idx.x == pos.x && idx.y == pos.y)return true;
	}
	return false;
}
