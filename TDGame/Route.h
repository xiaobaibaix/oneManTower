#pragma once

#include "Tile.h"
#include "Vector2D.h"

#include <SDL.h>
#include <vector>
//Â·Ïß
class Route
{
public:
	typedef std::vector<SDL_Point> IdxList;
public:
	Route() = default;
	Route(const TileMap& map, const SDL_Point& pos);;

	~Route() = default;

	const IdxList& get_idx_list();

private:
	IdxList idx_list;
private:
	bool check_duplicate_idx(const SDL_Point& pos);
};

