#include "Enemy_goblinPriest.h"

Enemy_goblinPriest::Enemy_goblinPriest(const Vector2D& pos, int dir)
{
	static Manager_config* config = Manager_config::instance();
	static Manager_resources* res = Manager_resources::instance();

	name = "goblinPriest";

	hp = hp_max = config->goblin_priest_template.hp;
	damage = config->goblin_priest_template.damage;
	v_const = v_max = config->goblin_priest_template.speed;
	reward_ratio = config->goblin_priest_template.reward_ratio;
	recover_range = config->goblin_priest_template.recover_range;
	recover_intensity = config->goblin_priest_template.recover_intensity;
	time_skill_cure.set_wait_time(config->goblin_priest_template.recover_interval);

	SDL_Texture* tex = res->get_texture_pool().find(ResID::Tex_GoblinPriest)->second;
	const int w = 5;
	const int h = 4;
	anim.set_texture(tex, w, h, {});

	anim.set_interval(0.1);

	idx_left = w * 3;
	idx_right = w * 2;
	idx_up = w * 1;
	idx_down = w * 0;

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

	this->pos = nex_pos = pos;

}

Enemy_goblinPriest::~Enemy_goblinPriest()
{
}

void Enemy_goblinPriest::on_update(double delta_time)
{
	Enemy::on_update(delta_time);
}

void Enemy_goblinPriest::on_draw(SDL_Renderer* render)
{
	Enemy::on_draw(render);
}
