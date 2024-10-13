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

	int terrain = 0;//����
	int decoration = -1;//װ��
	int speical_flag = -1;//�����־
	bool has_tower = false;
	Direction direction = Direction::None;//����
};

typedef std::vector<std::vector<Tile>> TileMap;
