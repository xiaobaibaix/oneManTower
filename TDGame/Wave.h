#pragma once


#include "EnemyType.h"

#include <vector>

struct Wave//���νṹ
{
	struct SpawnEvent//�����¼�
	{
		double interval = 0;
		int spawn_point = 1;//������
		EnemyType enemy_type = EnemyType::Slim;
	};

	double rewards = 0;//����
	double interval = 0;//ʱ����
	std::vector<SpawnEvent> spawn_event_list;//�����¼�
};

typedef std::vector<Wave> WaveList;

