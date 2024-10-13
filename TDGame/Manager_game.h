#pragma once

#include "Manager.h"

#include "Manager_config.h"
#include "Manager_resources.h"
#include "Manager_enemy.h"
#include "Manager_wave.h"
#include "Manager_tower.h"
#include "Manager_ui.h"

class Manager_game :public Manager<Manager_game>
{
	friend class Manager<Manager_game>;
public:
	int run(int argc, char** argv);

	const int& get_coin_count()const;
	const int& get_home_hp()const;

	void add_coin(int coins);//¼Ó½ð±Ò
	void dec_coin(int coins);//¼õ½ð±Ò
	void dec_home_hp();
public:
	bool is_debug = false;
protected:
	Manager_game();
	~Manager_game();

private:
	void on_input(const SDL_Event* event);

	void on_update(double delta_time);

	void on_draw();

	void init_assert(bool flag,const char* text);

	bool generate_tile_map_texture();
private:
	int FPS = 60;

	int cur_coin_count = 0;
	int cur_home_hp = 10;

	bool is_quit = false;


	SDL_Event event;

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	SDL_Texture* tex_tile_map = nullptr;

	//manager
	Manager_wave* manager_wave = nullptr;
	Manager_config* manager_config = nullptr;
	Manager_resources* manager_resources = nullptr;
	Manager_enemy* manager_enemy = nullptr;
	Manager_tower* manager_tower = nullptr;
	Manager_ui* manager_ui = nullptr;
};


