#include "Bullet.h"
#include "Tile.h"
#include "Vector2D.h"

#include "Manager_game.h"

Bullet::Bullet(const Vector2D& pos, const Vector2D& v)
{
	this->pos = pos;
	this->v = v;

	timer_stop.set_shot(1);
	timer_stop.set_callback([&]() { 
		std::cout << "can_remove is ture" << std::endl;
		can_remove = true; 
		}
	);
	timer_stop.set_wait_time(4);
}

void Bullet::on_update(double delta_time)
{
	if (valid) {
		ainm.on_update(delta_time);
		pos += v * delta_time * SIZE_TILE;
		pos_collision += v * delta_time * SIZE_TILE;
	}
	if (!can_remove)timer_stop.on_update(delta_time);

}

void Bullet::on_draw(SDL_Renderer* render)
{
	if (valid) {
		ainm.on_draw(render, { (int)pos.x,(int)pos.y });

		if (Manager_game::instance()->is_debug)filledCircleRGBA(render, pos_collision.x, pos_collision.y, 4, 255, 0, 0, 255);
	}
}

void Bullet::setDamage(double damage)
{
	this->damage = damage;
}

void Bullet::setCallback(std::function<void()> callback)
{
	this->callback = callback;
}

void Bullet::setHitEnemy(Enemy* enemy)
{
	this->hit_enemy = enemy;
}

bool Bullet::isValid()
{
	return valid;
}

bool Bullet::isRemove()
{
	return can_remove;
}

double Bullet::getDamage()
{
	return damage;
}


bool Bullet::on_collision(Enemy* enemey)
{
	if (!valid)return false;//无效的不用检测
	const Vector2D& enemy_cneter_pos= enemey->getPos()*SIZE_TILE+SIZE_TILE/2;

	if (pos_collision.x >= enemy_cneter_pos.x - enemey->getSize().x / 2 && pos_collision.x <= enemy_cneter_pos.x + enemey->getSize().x / 2 &&
		pos_collision.y >= enemy_cneter_pos.y - enemey->getSize().y / 2 && pos_collision.y <= enemy_cneter_pos.y + enemey->getSize().y / 2) {
		//std::cout << "on_collision!" << std::endl;
		valid = false;

		timer_stop.reset_pass_time();
		timer_stop.set_wait_time(0.05);
		return true;
	}
	return false;
}

void Bullet::reset(const Vector2D& pos, const Vector2D& v)
{
	this->pos = pos;
	this->v = v;

	valid = true;
	can_remove = false;

	ainm.restart();
	timer_stop.set_wait_time(4);
	timer_stop.restart();

}
