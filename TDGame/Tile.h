#pragma once

#include <vector>

#define SIZE_TILE 48

struct Tile
{
	enum class Direction
	{
		None,
		Up,
		Down,
		Left,
		Right
	};

	int terrain = 0;//地形
	int decoration = -1;//装饰
	int speical_flag = -1;//特殊标志
	bool has_tower = false;
	Direction direction = Direction::None;//方向
};

typedef std::vector<std::vector<Tile>> TileMap;
