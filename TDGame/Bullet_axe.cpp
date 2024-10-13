#include "Bullet_axe.h"
#include "Manager_resources.h"

Bullet_axe::Bullet_axe(const Vector2D& pos, const Vector2D& v):Bullet(pos,v)
{
	static SDL_Texture* tex = Manager_resources::instance()->get_texture_pool().find(ResID::Tex_BulletAxe)->second;
	int w, h;
	SDL_QueryTexture(tex, nullptr, nullptr, &w, &h);
	size.x = w;
	size.y = h;

	ainm.set_interval(0.1);
	ainm.set_texture(tex, 4, 2, {});
	ainm.set_begin(0);
	ainm.set_width(8);

	pos_collision = { pos.x + SIZE_TILE / 2,pos.y + SIZE_TILE / 2 };

}

void Bullet_axe::on_update(double delta_time)
{
	Bullet::on_update(delta_time);
	if (hit_enemy) {
		hit_enemy->decV(0.5);
		hit_enemy->set_slow_time(2);
		hit_enemy = nullptr;
	}
}

void Bullet_axe::reset(const Vector2D& pos, const Vector2D& v)
{
	Bullet::reset(pos, v);

	pos_collision = { pos.x + SIZE_TILE / 2,pos.y + SIZE_TILE / 2 };

}

