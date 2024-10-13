#pragma once

#include "Vector2D.h"
#include "Animation.h"
#include "Timer.h"
#include "Route.h"
#include "Manager_config.h"
#include "Manager_resources.h"

#include <SDL.h>
#include <string>

class Enemy
{
public:

	Enemy();
	virtual~Enemy()=default;

	void reset();

	void set_route(Route* route);
	void set_slow_time(double time);
	void set_recover_state(bool flag);

	void birth(const Vector2D& pos, int dir);
	void die();
	void arrive_home();

	const std::string& get_name();
	const Vector2D& getPos()const;
	const Vector2D& getV()const;
	const Vector2D& getSize()const;
	bool get_enemy_is_living();
	bool get_enemy_is_arrived();
	double getHP();

	void addHP(double hp);//��Ѫ
	void decHP(double hp);//��Ѫ
	void decV(double v_percent);//�԰ٷֱȷ�ʽ����

	virtual void on_update(double delta_time);
	virtual void on_draw(SDL_Renderer* render);
protected:
	std::string name;

	double hp;
	double hp_max;
	double v_const;
	double v_max;
	double damage;

	int idx_left;
	int idx_right;
	int idx_up;
	int idx_down;

	int pre_pos_idx = 0;

	Animation anim;

	Vector2D pos = { 0 };//��Ƭ����
	Vector2D nex_pos = {0};
	Vector2D v = { 0 };
	Vector2D dir = { 0 };
	Vector2D size = { 0 };//������ײ����

	Timer time_skill_cure;	//���Ƽ��ܶ�ʱ��
	Timer time_slow;		//���Ƽ��ܶ�ʱ��
	Timer time_recover;		//

	double reward_ratio;		//����Ҹ���
	double recover_range;		//���Ʒ�Χ
	double recover_intensity;	//����ǿ��

	Route* route = nullptr;		//·��

	bool isLiving = true;//�Ƿ���
	bool arrived = false;//�Ƿ񵽴��յ�
	bool is_recovering = false;//�Ƿ�����������
	bool is_be_recovering = false;//
private:

	void change_anim();
	void change_pos(double delta_time);


};

