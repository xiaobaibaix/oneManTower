#pragma once
#include "Tile.h"
#include "Route.h"

#include <SDL.h>
#include <string>
#include <sstream>
#include <fstream>
#include <unordered_map>

class Map
{
public:
	typedef std::unordered_map<int, Route> SpawnerRoutePool;
public:
	bool load(const std::string& path);

	size_t get_width() const;

	size_t get_Height() const;

	TileMap& get_tile_map();

	const SDL_Point& get_home_pos() const;

	SpawnerRoutePool* get_route_pool();

	void place_tower(const SDL_Point& pos);

	Map()=default;
	~Map()= default;
private:
	std::string trim_str(const std::string str);

	void load_tile_from_string(Tile& tile,const std::string& str);

	void generate_map_cache();
private:
	TileMap tile_map;
	SDL_Point home_pos = {0};
	SpawnerRoutePool route_pool;
};

