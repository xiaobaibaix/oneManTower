#include "Map.h"

bool Map::load(const std::string& path) {
	std::ifstream file(path);
	if (!file.good())return false;

	TileMap tile_map_temp;

	int idx_x = -1, idx_y = -1;

	std::string str_line;
	while (std::getline(file, str_line))
	{
		str_line = trim_str(str_line);

		if (str_line == "")continue;

		tile_map_temp.emplace_back();

		idx_x = -1; idx_y++;

		std::string str_tile;
		std::stringstream str_stream(str_line);
		while (std::getline(str_stream, str_tile, ','))
		{
			idx_x++;
			tile_map_temp[idx_y].emplace_back();
			Tile& tile = tile_map_temp[idx_y].back();

			load_tile_from_string(tile, str_tile);
		}
	}
	file.close();

	if (tile_map_temp.empty() || tile_map_temp[0].empty())return false;
	tile_map = tile_map_temp;

	generate_map_cache();

	return true;
}

size_t Map::get_width() const {
	if (tile_map.empty())return 0;
	return tile_map[0].size();
}

size_t Map::get_Height() const {
	return tile_map.size();
}

TileMap& Map::get_tile_map(){
	return tile_map;
}

const SDL_Point& Map::get_home_pos() const {
	return home_pos;
}

Map::SpawnerRoutePool* Map::get_route_pool(){
	return &route_pool;
}

void Map::place_tower(const SDL_Point& pos) {
	tile_map[pos.y][pos.x].has_tower = true;
}

std::string Map::trim_str(const std::string str) {//干净字符串

	size_t begin_idx = str.find_first_not_of(" \t");
	if (begin_idx == std::string::npos)return "";

	size_t end_idx = str.find_last_not_of(" \t");
	size_t idx_range = end_idx - begin_idx + 1;

	return str.substr(begin_idx, idx_range);
}

void Map::load_tile_from_string(Tile& tile, const std::string& str) {

	std::string new_str = trim_str(str);

	std::string str_value;
	std::vector<int> values;
	std::stringstream str_stream(new_str);

	while (std::getline(str_stream, str_value, '\\'))
	{
		int value;
		try
		{
			value = std::stoi(str_value);
		}
		catch (const std::exception&)
		{
			value = -1;
		}
		values.push_back(value);
	}
	tile.terrain = (values.size() < 1 || values[0] < 0) ? 0 : values[0];
	tile.decoration = (values.size() < 2) ? -1 : values[1];
	tile.direction = (Tile::Direction)((values.size() < 3 || values[2] < 0) ? 0 : values[2]);
	tile.speical_flag = (values.size() <= 3) ? -1 : values[3];
}

void Map::generate_map_cache() {//生成缓存
	for (int y = 0; y < get_Height(); y++) {
		for (int x = 0; x < get_width(); x++) {
			const Tile& tile = tile_map[y][x];
			if (tile.speical_flag<0) {//没有特殊标志
				continue;
			}
			if (tile.speical_flag == 0) {//特殊标志为房屋
				home_pos.x = x;
				home_pos.y = y;
			}
			if(tile.speical_flag > 0){//特殊标志为洋流箭头方向
				route_pool[tile.speical_flag] = Route(tile_map, { x,y });
			}

		}
	}
}
