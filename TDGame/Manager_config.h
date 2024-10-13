#pragma once

#include "Manager.h"
#include "cJSON.h"
#include "Map.h"
#include "Wave.h"



class Manager_config:public Manager<Manager_config>
{
	friend class Manager<Manager_config>;
public:
	struct BasicTemplate
	{
		std::string window_title = u8"村庄保卫战";
		int window_width = 0;
		int window_height = 0;
	};
	struct PlayerTemplate
	{
		double speed = 3;
		double normal_attack_interval = 0.5;
		double normal_attack_damage = 0;
		double skill_interval = 10;
		double skill_damage = 1;
	};

	struct TowerTemplate
	{
		double interval[10] = { 1 };	//时间间隔
		double damage[10] = { 25 };		//伤害
		double view_range[10] = { 5 };	//视野范围
		double cost[10] = { 50 };		//建造花费
		double upgrade_cost[9] = { 75 };	//升级花费
	};

	struct EnemyTemplate
	{
		double hp = 100;//生命值
		double speed = 1;//移动速度
		double damage = 1;//对家的伤害
		double reward_ratio = 0.5;//爆金币的概念
		double recover_interval = 10;//恢复时间间隔
		double recover_range = 0;//恢复范围半径
		double recover_intensity = 25;//恢复量
	};
public: 
	Map map;//地图
	std::vector<Wave> wave_list;//波次列表

	bool is_game_win = true;
	bool is_game_over = false;

	SDL_Rect rect_tile_map = { 0 };//房子的位置矩行

	BasicTemplate basic_template;

	PlayerTemplate player_template;

	TowerTemplate  archer_template;
	TowerTemplate  axeman_template;
	TowerTemplate  gunner_template;

	EnemyTemplate slim_template;
	EnemyTemplate king_slim_template;
	EnemyTemplate skeleton_template;
	EnemyTemplate goblin_template;
	EnemyTemplate goblin_priest_template;

	const double num_initial_hp = 10;//家的血量
	const double num_initial_coin = 10000;//初始金币数
	const double num_coin_per_prop = 10;//捡到的金币数
public:
	bool load_level_config(const std::string path);
	bool laod_game_config(const std::string path);
protected:
	Manager_config()=default;
	~Manager_config()= default;

private:
	void prase_basic_template(BasicTemplate& tp1, cJSON* root);

	void prase_player_template(PlayerTemplate& tp1, cJSON* root);

	void prase_number_array(double* arry, int len, cJSON* root);

	void prase_tower_template(TowerTemplate& tp1, cJSON* root);

	void prase_enemy_template(EnemyTemplate& tp1, cJSON* root);
};

