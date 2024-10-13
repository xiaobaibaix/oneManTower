#pragma once
#include "Vector2D.h"
#include "Animation.h"
#include "Manager_resources.h"
#include "Enemy.h"

class Bullet
{
public:
	Bullet(const Vector2D& pos, const Vector2D& v);
	virtual~Bullet() = default;

	virtual void on_update(double delta_time);
	virtual void on_draw(SDL_Renderer* render);

	void setDamage(double damage);
	void setCallback(std::function<void()> callback);
	void setHitEnemy(Enemy* enemy);

	bool isValid();
	bool isRemove();
	double getDamage();

	bool on_collision(Enemy* enemey);

	virtual void reset(const Vector2D& pos, const Vector2D& v);
protected:

	Vector2D pos = {0};
	Vector2D v = {0};
	Vector2D size = {0};
	Vector2D pos_collision = {0};//�������꣬��ײ��

	Animation ainm;

	Timer timer_stop;

	double damage = 0;

	bool valid = true;//��Ч
	bool can_remove = false;//�Ƿ�����Ƴ�

	Enemy* hit_enemy = nullptr;//���еĵ���

	std::function<void()> callback;
};

