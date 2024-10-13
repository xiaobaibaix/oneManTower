#pragma once
#include "Vector2D.h"
#include "Animation.h"
#include "Timer.h"
#include "Manager_config.h"
#include "Manager_resources.h"
#include "Bullet_axe.h"
#include "Enemy.h"

class Tower
{
public:
	friend class Manager_tower;
public:
	Tower();
	virtual~Tower() = default;

	virtual void on_update(double delta_time);
	virtual void on_draw(SDL_Renderer* render);

	bool addGrade();//升级
	const Vector2D& getPos()const;
	double getViewRange();
	const std::vector<Bullet*>& getBulletList()const;
	
	virtual bool fire(const Vector2D& dir);

	void setSelect(bool flag);
	bool getSelect();
protected:
	//模板信息
	double const* interval = nullptr;	//攻击时间间隔
	double const* damage = nullptr;		//攻击伤害
	double const* view_range = nullptr;	//视野范围
	double const* cost = nullptr;		//建造花销
	double const* upgrade_cost =nullptr;//升级花销

	double bullet_speed = 0;//子弹移动的速度
	
	bool can_fire = true;//是否可以开火
	bool lose_target = true;//目标是否丢失

	int idx_grade = 0;//等级下标
	
	Enemy* locked_target =nullptr;//被锁定的敌人

	Timer timer_fire;//开火定时器

	Animation anim;//动画

	Vector2D pos;//塔的坐标
	Vector2D dir;//面朝向

	std::vector<Bullet*> bullet_list;

private:
	bool inViewRange(const Vector2D& pos);
};

