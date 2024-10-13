#include "Bullet_arrow.h"
#include "Manager_game.h"

Bullet_arrow::Bullet_arrow(const Vector2D& pos, const Vector2D& v):Bullet(pos,v)
{
	static SDL_Texture* tex = Manager_resources::instance()->get_texture_pool().find(ResID::Tex_BulletArrow)->second;
	int w, h;
	SDL_QueryTexture(tex, nullptr, nullptr, &w, &h);
	size.x = w;
	size.y = h;

	ainm.set_interval(0.1);
	ainm.set_texture(tex, 2, 1, {});
	ainm.set_begin(0);

	double radians = atan2(v.y, v.x);
	thta = radians * (180.0 / M_PI);

	pos_collision = { pos .x + SIZE_TILE / 2,pos.y+SIZE_TILE/2};
	pos_collision += v*3;

}

void Bullet_arrow::on_update(double delta_time)
{
	Bullet::on_update(delta_time);
	if (hit_enemy) {


		hit_enemy = nullptr;
	}
}

void Bullet_arrow::on_draw(SDL_Renderer* render)
{
	if(valid)ainm.on_draw(render, { (int)pos.x,(int)pos.y }, thta);

	if (Manager_game::instance()->is_debug)filledCircleRGBA(render, pos_collision.x, pos_collision.y, 4, 255, 0, 0, 255);


}

void Bullet_arrow::reset(const Vector2D& pos, const Vector2D& v)
{
	Bullet::reset(pos, v);
	double radians = atan2(v.y, v.x);
	thta = radians * (180.0 / M_PI);

	pos_collision = { pos.x + SIZE_TILE / 2,pos.y + SIZE_TILE / 2 };
	pos_collision += v * 3;
}
