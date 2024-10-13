#include "Tower_archer.h"
#include "Bullet_arrow.h"

Tower_archer::Tower_archer(int idx_x, int idx_y)
{
	pos.x = idx_x;
	pos.y = idx_y;

	static auto& template_tower = Manager_config::instance()->archer_template;
	interval = template_tower.interval;
	damage = template_tower.damage;
	view_range = template_tower.view_range;
	cost = template_tower.cost;
	upgrade_cost = template_tower.upgrade_cost;

	timer_fire.set_wait_time(interval[idx_grade]);

	anim.set_interval(interval[idx_grade] / 2);
	SDL_Texture* tex = Manager_resources::instance()->get_texture_pool().find(ResID::Tex_Archer)->second;

	anim.set_texture(tex, 3, 8, { 2,5,8,11});
	anim.set_begin(0);
	anim.set_width(2);
	anim.set_idx_callback(0);

	bullet_speed = 4;
}

Tower_archer::~Tower_archer()
{
}

void Tower_archer::on_update(double delta_time)
{
	Tower::on_update(delta_time);
	if (!lose_target) {
		double radians = atan2(dir.y, dir.x);
		double thta = -radians * (180.0 / M_PI);

		if (thta > -45 && thta <= 45) {//ср
			anim.set_begin(21);
		}
		else if (thta > 45 && thta <= 135) {//ио
			anim.set_begin(15);
		}
		else if (thta > -135 && thta <= -45) {//об
			anim.set_begin(12);
		}
		else {//вС
			anim.set_begin(18);
		}

		anim.set_interval(interval[idx_grade] / 3);
		anim.set_width(3);
	}
	else {
		if (anim.get_idx_frame() == 2)anim.restart();
		if (anim.get_begin() >= 12)anim.set_begin(anim.get_begin()-12);
		anim.set_width(2);
		anim.set_interval(interval[idx_grade] / 2);
	}
}

bool Tower_archer::fire(const Vector2D& dir)
{
	if (Tower::fire(dir)) {
		std::cout << "reset archer bullet:" << bullet_list.size() << std::endl;
		return true;
	}

	bullet_list.push_back(new Bullet_arrow(pos * SIZE_TILE, dir * bullet_speed));
	bullet_list.back()->setDamage(damage[idx_grade]);

	std::cout << "archer bullet:" << bullet_list.size() << std::endl;
	return true;
}
