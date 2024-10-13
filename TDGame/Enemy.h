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

	void addHP(double hp);//加血
	void decHP(double hp);//减血
	void decV(double v_percent);//以百分比方式减速

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

	Vector2D pos = { 0 };//瓦片坐标
	Vector2D nex_pos = {0};
	Vector2D v = { 0 };
	Vector2D dir = { 0 };
	Vector2D size = { 0 };//像素碰撞矩形

	Timer time_skill_cure;	//治疗技能定时器
	Timer time_slow;		//治疗技能定时器
	Timer time_recover;		//

	double reward_ratio;		//爆金币概率
	double recover_range;		//治疗范围
	double recover_intensity;	//治疗强度

	Route* route = nullptr;		//路线

	bool isLiving = true;//是否存活
	bool arrived = false;//是否到达终点
	bool is_recovering = false;//是否真正被治疗
	bool is_be_recovering = false;//
private:

	void change_anim();
	void change_pos(double delta_time);


};

