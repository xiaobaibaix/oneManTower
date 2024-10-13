#include "Bullet_shell.h"
#include "Manager_enemy.h"
#include "Manager_game.h"

Bullet_shell::Bullet_shell(const Vector2D& pos, const Vector2D& v):Bullet(pos,v)
{
	static SDL_Texture* tex = Manager_resources::instance()->get_texture_pool().find(ResID::Tex_BulletShell)->second;
	static SDL_Texture* tex_explode = Manager_resources::instance()->get_texture_pool().find(ResID::Tex_EffectExplode)->second;
	int w, h;
	SDL_QueryTexture(tex, nullptr, nullptr, &w, &h);
	size.x = w;
	size.y = h;

	ainm.set_interval(0.1);
	ainm.set_texture(tex, 2, 1, {});

	ainm_explode.set_is_loop(false,1);
	ainm_explode.set_texture(tex_explode, 5, 1, {});
	ainm_explode.set_interval(0.1);

	pos_collision = { pos.x + SIZE_TILE / 2,pos.y + SIZE_TILE / 2 };

	hit_range = 1;
	spurting = 0.8;
}

void Bullet_shell::on_update(double delta_time)
{
	Bullet::on_update(delta_time);
	ainm_explode.on_update(delta_time);
	
	if (hit_enemy) {
		std::cout << "hit enemy!" << std::endl;

		static auto& enemy_list = Manager_enemy::instance()->get_enemys_list();

		for (auto& enemy : enemy_list) {
			if (!enemy->get_enemy_is_living())continue;
			if (enemy == hit_enemy)continue;
			
			const Vector2D center_pos = { enemy ->getPos().x* SIZE_TILE +SIZE_TILE/2,enemy->getPos().y*SIZE_TILE + SIZE_TILE / 2 };
			const float distence = (center_pos - this->pos_collision).getMode_length();

			if (distence<SIZE_TILE*2) {//相距不要太长
				//以斜边与最短边计算出之间的平均长度作为半径

				//std::cout << "distence: " << distence << std::endl;

				float size_x_r = enemy->getSize().x/2;
				float size_y_r = enemy->getSize().y/2;

				float slant = sqrt(size_x_r * size_x_r + size_y_r * size_y_r);

				float r = (slant + (size_x_r >= size_y_r ? size_y_r : size_x_r)) / 2;
				//std::cout << "enemy circle r:" << r<<" ";

				if (in_hit_range(center_pos, r)) {
					std::cout << "hit ----------" << std::endl;
					enemy->decHP(damage* spurting);
					enemy->decV(spurting);
				}
			}
		}
		ainm_explode.restart();
		timer_stop.set_wait_time(ainm_explode.get_interval() * ainm_explode.get_width());
		hit_enemy = nullptr;
	}
}

void Bullet_shell::on_draw(SDL_Renderer* render)
{
	Bullet::on_draw(render);
	if (!valid) {
		if (!can_remove) {
			ainm_explode.on_draw(render, { (int)pos.x - SIZE_TILE / 2,(int)pos.y - SIZE_TILE / 2 });
			if (Manager_game::instance()->is_debug)filledCircleRGBA(render, pos_collision.x, pos_collision.y, hit_range * SIZE_TILE,255,0,0,50);
		}
	}
}

void Bullet_shell::reset(const Vector2D& pos, const Vector2D& v)
{
	Bullet::reset(pos, v);

	pos_collision = { pos.x + SIZE_TILE / 2,pos.y + SIZE_TILE / 2 };

}

bool Bullet_shell::in_hit_range(const Vector2D& srcpos, float idx_r)
{
	return ((srcpos - pos_collision).getMode_length() <= (idx_r + this->hit_range*SIZE_TILE))?true:false;
}
