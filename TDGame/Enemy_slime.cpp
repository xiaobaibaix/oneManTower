#include "Enemy_slime.h"

Enemy_slime::Enemy_slime(const Vector2D& pos,int dir)
{
	static Manager_config* config = Manager_config::instance();
	static Manager_resources* res = Manager_resources::instance();
	
	name = "slime";

	hp=hp_max=config->slim_template.hp;
	damage = config->slim_template.damage;
	v_const = v_max = config->slim_template.speed;
	reward_ratio = config->slim_template.reward_ratio;
	recover_range = config->slim_template.recover_range;
	recover_intensity = config->slim_template.recover_intensity;
	time_skill_cure.set_wait_time(config->slim_template.recover_interval);

	SDL_Texture* tex = res->get_texture_pool().find(ResID::Tex_Slime)->second;
	anim.set_texture(tex, 6, 4, {});

	anim.set_interval(0.1);

	idx_left = 6 * 3;
	idx_right = 6 * 2;
	idx_up = 6 * 1;
	idx_down=6 * 0;

	switch (dir)
	{
	case 1://up
		anim.set_begin(idx_up);
		break;
	case 2://down
		anim.set_begin(idx_down);
		break;
	case 3://left
		anim.set_begin(idx_left);
		break;
	case 4://right
		anim.set_begin(idx_right);
		break;
	default:
		break;
	}

	this->pos =nex_pos= pos;

	size = { SIZE_TILE / 2 * 1.2,SIZE_TILE / 2 *1.2 };


}

Enemy_slime::~Enemy_slime()
{
}

void Enemy_slime::on_update(double delta_time)
{
	Enemy::on_update(delta_time);
}

void Enemy_slime::on_draw(SDL_Renderer* render)
{
	Enemy::on_draw(render);

}
