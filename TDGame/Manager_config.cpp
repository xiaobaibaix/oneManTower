#include"Manager_config.h"

bool Manager_config::load_level_config(const std::string path) {//加载关卡数据
	std::ifstream file(path);

	if (!file.good())return false;

	std::stringstream str_stream;
	str_stream << file.rdbuf();
	file.close();

	cJSON* json_root = cJSON_Parse(str_stream.str().c_str());//解析文件
	if (!json_root)return false;

	if (json_root->type != cJSON_Array) {
		cJSON_Delete(json_root);
		return false;
	}

	cJSON* json_wave = nullptr;
	cJSON_ArrayForEach(json_wave, json_root) {
		if (json_wave->type != cJSON_Object) continue;

		wave_list.emplace_back();
		Wave& wave = wave_list.back();

		cJSON* json_wave_reward = cJSON_GetObjectItem(json_wave, "rewards");
		if (json_wave_reward && json_wave_reward->type == cJSON_Number)wave.rewards = json_wave_reward->valuedouble;
		cJSON* json_wave_interval = cJSON_GetObjectItem(json_wave, "interval");
		if (json_wave_interval && json_wave_interval->type == cJSON_Number)wave.interval = json_wave_interval->valuedouble;

		cJSON* json_wave_spawn_list = cJSON_GetObjectItem(json_wave, "spawn_list");
		if (json_wave_spawn_list && json_wave_spawn_list->type == cJSON_Array)
		{
			cJSON* json_spawn_event = nullptr;
			cJSON_ArrayForEach(json_spawn_event, json_wave_spawn_list)
			{
				if (json_spawn_event && json_spawn_event->type != cJSON_Object)continue;

				wave.spawn_event_list.emplace_back();
				Wave::SpawnEvent& spawn_event = wave.spawn_event_list.back();

				cJSON* json_spawn_event_interval = cJSON_GetObjectItem(json_spawn_event, "interval");
				if (json_spawn_event_interval && json_spawn_event_interval->type == cJSON_Number)
					spawn_event.interval = json_spawn_event_interval->valuedouble;
				cJSON* json_spawn_event_spawn_point = cJSON_GetObjectItem(json_spawn_event, "point");
				if (json_spawn_event_spawn_point && json_spawn_event_spawn_point->type == cJSON_Number)
					spawn_event.spawn_point = json_spawn_event_spawn_point->valueint;

				cJSON* json_spawn_event_enemy_type = cJSON_GetObjectItem(json_spawn_event, "enemy");
				if (json_spawn_event_enemy_type && json_spawn_event_enemy_type->type == cJSON_String)
				{
					const std::string str_enemy = json_spawn_event_enemy_type->valuestring;
					if (str_enemy == "Slim") {
						spawn_event.enemy_type = EnemyType::Slim;
					}
					else if (str_enemy == "KingSlim") {
						spawn_event.enemy_type = EnemyType::KingSlim;
					}
					else if (str_enemy == "Skeleton") {
						spawn_event.enemy_type = EnemyType::Skeleton;
					}
					else if (str_enemy == "Goblin") {
						spawn_event.enemy_type = EnemyType::Goblin;
					}
					else if (str_enemy == "GoblinPriest") {
						spawn_event.enemy_type = EnemyType::GoblinPriest;
					}
				}
				if (wave.spawn_event_list.empty())
					wave_list.pop_back();
			}
		}
	}
	cJSON_Delete(json_root);
	//再次检测最顶层wave_list是否为空
	if (wave_list.empty())return false;
	return true;
}

bool Manager_config::laod_game_config(const std::string path) {//加载游戏角色数据
	std::ifstream file(path);
	if (!file.good())return false;

	std::stringstream str_stream;
	str_stream << file.rdbuf();
	file.close();

	cJSON* json_root = cJSON_Parse(str_stream.str().c_str());
	if (!json_root || json_root->type != cJSON_Object)return false;

	cJSON* json_basic = cJSON_GetObjectItem(json_root, "basic");
	cJSON* json_player = cJSON_GetObjectItem(json_root, "player");
	cJSON* json_tower = cJSON_GetObjectItem(json_root, "tower");
	cJSON* json_enemy = cJSON_GetObjectItem(json_root, "enemy");

	if (!json_basic || !json_player || !json_tower || !json_enemy
		|| json_basic->type != cJSON_Object
		|| json_player->type != cJSON_Object
		|| json_tower->type != cJSON_Object
		|| json_enemy->type != cJSON_Object
		) {
		cJSON_Delete(json_root);
		return false;
	}
	prase_basic_template(basic_template, json_basic);

	prase_player_template(player_template, json_player);

	prase_tower_template(archer_template, cJSON_GetObjectItem(json_tower, "archer"));
	prase_tower_template(axeman_template, cJSON_GetObjectItem(json_tower, "axeman"));
	prase_tower_template(gunner_template, cJSON_GetObjectItem(json_tower, "gunner"));

	prase_enemy_template(slim_template, cJSON_GetObjectItem(json_enemy, "slim"));
	prase_enemy_template(king_slim_template, cJSON_GetObjectItem(json_enemy, "king_slim"));
	prase_enemy_template(skeleton_template, cJSON_GetObjectItem(json_enemy, "skeleton"));
	prase_enemy_template(goblin_template, cJSON_GetObjectItem(json_enemy, "goblin"));
	prase_enemy_template(goblin_priest_template, cJSON_GetObjectItem(json_enemy, "goblin_priest"));

	cJSON_Delete(json_root);
	return true;
}

void Manager_config::prase_basic_template(BasicTemplate& tp1, cJSON* root) {
	if (!root || root->type != cJSON_Object)return;

	cJSON* json_window_title = cJSON_GetObjectItem(root, "window_title");
	cJSON* json_window_width = cJSON_GetObjectItem(root, "window_width");
	cJSON* json_window_height = cJSON_GetObjectItem(root, "window_height");

	if (json_window_title && json_window_title->type == cJSON_String)
		tp1.window_title = json_window_title->valuestring;
	if (json_window_width && json_window_width->type == cJSON_Number)
		tp1.window_width = json_window_width->valueint;
	if (json_window_height && json_window_height->type == cJSON_Number)
		tp1.window_height = json_window_height->valueint;

}

void Manager_config::prase_player_template(PlayerTemplate& tp1, cJSON* root) {
	if (!root || root->type != cJSON_Object)return;

	cJSON* json_speed = cJSON_GetObjectItem(root, "speed");
	cJSON* json_normal_attack_interval = cJSON_GetObjectItem(root, "normal_attack_interval");
	cJSON* json_normal_attack_damage = cJSON_GetObjectItem(root, "normal_attack_damage");
	cJSON* json_skill_interval = cJSON_GetObjectItem(root, "skill_interval");
	cJSON* json_skill_damage = cJSON_GetObjectItem(root, "skill_damage");

	if (json_speed && json_speed->type == cJSON_Number)
		tp1.speed = json_speed->valuedouble;
	if (json_normal_attack_interval && json_normal_attack_interval->type == cJSON_Number)
		tp1.normal_attack_interval = json_normal_attack_interval->valuedouble;
	if (json_normal_attack_damage && json_normal_attack_damage->type == cJSON_Number)
		tp1.normal_attack_damage = json_normal_attack_damage->valuedouble;
	if (json_skill_interval && json_skill_interval->type == cJSON_Number)
		tp1.skill_interval = json_skill_interval->valuedouble;
	if (json_skill_damage && json_skill_damage->type == cJSON_Number)
		tp1.skill_damage = json_skill_damage->valuedouble;
}

void Manager_config::prase_number_array(double* arry, int len, cJSON* root) {
	if (!root || root->type != cJSON_Array)return;

	int idx = -1;
	cJSON* json_idx = nullptr;
	cJSON_ArrayForEach(json_idx, root) {
		idx++;
		if (json_idx->type != cJSON_Number || idx >= len)continue;
		arry[idx] = json_idx->valuedouble;
	}
}

void Manager_config::prase_tower_template(TowerTemplate& tp1, cJSON* root) {
	if (!root || root->type != cJSON_Object)return;

	cJSON* json_interval = cJSON_GetObjectItem(root, "interval");
	cJSON* json_damage = cJSON_GetObjectItem(root, "damage");
	cJSON* json_view_range = cJSON_GetObjectItem(root, "view_range");
	cJSON* json_cost = cJSON_GetObjectItem(root, "cost");
	cJSON* json_upgrade_cost = cJSON_GetObjectItem(root, "upgrade_cost");

	prase_number_array(tp1.interval, 10, json_interval);
	prase_number_array(tp1.damage, 10, json_damage);
	prase_number_array(tp1.view_range, 10, json_view_range);
	prase_number_array(tp1.cost, 10, json_cost);
	prase_number_array(tp1.upgrade_cost, 9, json_upgrade_cost);
}

void Manager_config::prase_enemy_template(EnemyTemplate& tp1, cJSON* root) {
	if (!root || root->type != cJSON_Object)return;

	cJSON* json_hp = cJSON_GetObjectItem(root, "hp");
	cJSON* json_speed = cJSON_GetObjectItem(root, "speed");
	cJSON* json_damage = cJSON_GetObjectItem(root, "damage");
	cJSON* json_reward_ratio = cJSON_GetObjectItem(root, "reward_ratio");
	cJSON* json_recover_interval = cJSON_GetObjectItem(root, "recover_interval");
	cJSON* json_recover_range = cJSON_GetObjectItem(root, "recover_range");
	cJSON* json_recover_intensity = cJSON_GetObjectItem(root, "recover_intensity");

	if (json_hp && json_hp->type == cJSON_Number)tp1.hp = json_hp->valuedouble;
	if (json_speed && json_speed->type == cJSON_Number)tp1.speed = json_speed->valuedouble;
	if (json_damage && json_damage->type == cJSON_Number)tp1.damage = json_damage->valuedouble;
	if (json_reward_ratio && json_reward_ratio->type == cJSON_Number)tp1.reward_ratio = json_reward_ratio->valuedouble;
	if (json_recover_interval && json_recover_interval->type == cJSON_Number)tp1.recover_interval = json_recover_interval->valuedouble;
	if (json_recover_range && json_recover_range->type == cJSON_Number)tp1.recover_range = json_recover_range->valuedouble;
	if (json_recover_intensity && json_recover_intensity->type == cJSON_Number)tp1.recover_intensity = json_recover_intensity->valuedouble;
}
