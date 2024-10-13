#pragma once


#include "EnemyType.h"

#include <vector>

struct Wave//波次结构
{
	struct SpawnEvent//生成事件
	{
		double interval = 0;
		int spawn_point = 1;//引发点
		EnemyType enemy_type = EnemyType::Slim;
	};

	double rewards = 0;//奖励
	double interval = 0;//时间间隔
	std::vector<SpawnEvent> spawn_event_list;//生成事件
};

typedef std::vector<Wave> WaveList;

