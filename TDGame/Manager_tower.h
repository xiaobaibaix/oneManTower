#pragma once
#include "Manager.h"
#include "Tower.h"
#include "TowerType.h"
#include "Tile.h"

class Manager_tower :public Manager<Manager_tower>
{
	friend class Manager<Manager_tower>;
public:
	bool generate_tower(const Vector2D& pos,TowerType type);//������
	bool update_tower(const Vector2D& pos);//������
	bool update_tower(int idx_pos);
	
	void delete_all_tower();//ɾ��������
	void delete_tower();//ɾ����

	const std::vector<Tower*>& getTowerList()const;


	void on_update(double delta_time);
	void on_draw(SDL_Renderer* render);

protected:
	Manager_tower();
	~Manager_tower() = default;

private:

	TileMap *tile_map=nullptr;

	std::vector<Tower*> tower_list;
private:


};

