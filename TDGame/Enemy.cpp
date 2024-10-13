#include "Enemy.h"
#include "Manager_config.h"
#include "Manager_game.h"


Enemy::Enemy()
{
	anim.set_is_loop(true);

	time_skill_cure.set_shot(1);
	time_skill_cure.set_callback([&]() {
		static const std::list<Enemy*>& enemy_list = Manager_enemy::instance()->get_enemys_list();
		if (recover_range < 0) {
			this->addHP(recover_intensity);
			this->set_recover_state(false);//主动恢复
		}
		for (auto& enemy : enemy_list) {
			if (!enemy->get_enemy_is_living())continue;
			const Vector2D center_pos_ = { enemy->getPos().x * SIZE_TILE + SIZE_TILE / 2,enemy->getPos().y * SIZE_TILE + SIZE_TILE / 2 };
			const Vector2D center_pos_this = { pos.x * SIZE_TILE + SIZE_TILE / 2,pos.y * SIZE_TILE + SIZE_TILE / 2 };

			const float distence = (center_pos_ - center_pos_this).getMode_length();

			if (distence > recover_range * SIZE_TILE)continue;
			enemy->addHP(recover_intensity);
			enemy->set_recover_state(true);//被恢复
		}
		time_skill_cure.restart();
		}
	);

	time_slow.set_shot(1);
	time_slow.set_callback([&]() {v_const = v_max;});

	time_recover.set_shot(1);
	time_recover.set_wait_time(0.2);
	time_recover.set_callback([&]() {
		//std::cout << "is_recovering false=========================" << std::endl;
		is_recovering = false;
		is_be_recovering = false;
		}
	);

	size = { SIZE_TILE/2,SIZE_TILE /4*3 };
}

void Enemy::reset()
{
	hp = hp_max;
}

void Enemy::set_route(Route* route)
{
	this->route = route;
}

void Enemy::set_slow_time(double time)
{
	this->time_slow.set_wait_time(time);
	time_slow.restart();
}

void Enemy::set_recover_state(bool flag)
{
	is_be_recovering = flag;
}

void Enemy::birth(const Vector2D& pos, int dir)
{
	hp = hp_max;
	v_const = v_max;

	pre_pos_idx = 0;
	nex_pos = {0};
	v = { 0 };
	this->dir = { 0 };

	anim.restart();

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

	isLiving = true;
	arrived = false;
}

bool Enemy::get_enemy_is_living()
{
	return isLiving;
}

void Enemy::die()
{
	isLiving = false;
}

void Enemy::arrive_home()
{
	arrived = true;
}

bool Enemy::get_enemy_is_arrived()
{
	return arrived;
}

const std::string& Enemy::get_name()
{
	return name;
}

const Vector2D& Enemy::getPos() const
{
	return pos;
}

const Vector2D& Enemy::getV() const
{
	return v;
}

const Vector2D& Enemy::getSize() const
{
	return size;
}

void Enemy::addHP(double hp)
{
	this->hp += hp;
	if (this->hp >= hp_max)this->hp = hp_max;
	is_recovering = true;
	time_recover.restart();
}

void Enemy::decHP(double hp)
{
	if (!isLiving)return;
	std::cout << "decHP" << std::endl;
	this->hp -= hp;
	if (this->hp <= 0) {
		std::cout << "die" << std::endl;
		isLiving = false;

	}
}

void Enemy::decV(double v_percent)//百分比输入
{
	time_slow.restart();
	v_const = v_max * v_percent > v_const ? v_const : v_max * v_percent;
}

double Enemy::getHP()
{
	return hp;
}

void Enemy::on_update(double delta_time)
{
	anim.on_update(delta_time);
	time_skill_cure.on_update(delta_time);
	time_slow.on_update(delta_time);
	time_recover.on_update(delta_time);

	change_pos(delta_time);
	change_anim();

}

void Enemy::on_draw(SDL_Renderer* render)
{
	if (is_recovering) {
		//画加号
		SDL_Rect rect = { pos.x * SIZE_TILE + SIZE_TILE / 2-10 ,pos.y*SIZE_TILE-10,20,20};
		static SDL_Texture* tex = Manager_resources::instance()->get_texture_pool().find(ResID::Tex_UIRecover)->second;
		SDL_RenderCopy(render, tex, nullptr, &rect);
		if(recover_range>=0) {//别人
			//画范围
			filledCircleRGBA(render, pos.x * SIZE_TILE + SIZE_TILE / 2, pos.y * SIZE_TILE + SIZE_TILE / 2,recover_range*SIZE_TILE, 0, 255, 0, 20);
		}
	}
	anim.on_draw(render, { (int)(pos.x * SIZE_TILE),(int)(pos.y * SIZE_TILE) });

	if (Manager_game::instance()->is_debug) {
		SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
		const SDL_Rect rect = {pos.x*SIZE_TILE+SIZE_TILE/2-size.x/2,pos.y * SIZE_TILE + SIZE_TILE /2 - size.y / 2,size.x ,size.y };
		SDL_RenderDrawRect(render, &rect);
	}

	if (hp<hp_max) {
		const SDL_Rect rect = { pos.x*SIZE_TILE,pos.y* SIZE_TILE,SIZE_TILE*((hp/hp_max<=0)?0:(hp/hp_max)),10 };
		const SDL_Rect rect_ = { pos.x* SIZE_TILE,pos.y* SIZE_TILE,SIZE_TILE ,10 };
		SDL_SetRenderDrawColor(render, 255, 0, 0, 100);
		SDL_RenderFillRect(render, &rect);
		SDL_SetRenderDrawColor(render, 255, 255, 255, 120);
		SDL_RenderDrawRect(render, &rect_);
	}
}

void Enemy::change_anim()
{
	if (dir.x > 0) {
		anim.set_begin(idx_right);
	}
	else if (dir.x < 0) {
		anim.set_begin(idx_left);
	}
	else if (dir.y > 0) {
		anim.set_begin(idx_down);
	}
	else if (dir.y < 0) {
		anim.set_begin(idx_up);
	}
}

void Enemy::change_pos(double delta_time)
{
	if (pre_pos_idx + 1 < route->get_idx_list().size()) {

		if ((nex_pos - pos).about_zero()) {
			nex_pos = { (float)route->get_idx_list().at(pre_pos_idx + 1).x,(float)route->get_idx_list().at(pre_pos_idx + 1).y };

			dir.x = route->get_idx_list().at(pre_pos_idx + 1).x - route->get_idx_list().at(pre_pos_idx).x;
			dir.y = route->get_idx_list().at(pre_pos_idx + 1).y - route->get_idx_list().at(pre_pos_idx).y;

		}
	}
	else {
		dir = { 0 };
	}
	 
	v = dir * v_const;
	pos += v * delta_time;

	static const Vector2D pos_home = { (float)Manager_config::instance()->map.get_home_pos().x, (float)Manager_config::instance()->map.get_home_pos().y };

	auto move_distence = (nex_pos - pos);
	const auto move_result = move_distence * dir;
	if (move_distence.about_zero()) {
		pos = nex_pos;
		pre_pos_idx++;
		if (pos == pos_home) {
			Manager_game::instance()->dec_home_hp();
			std::cout << name << " arrive" << std::endl;
			isLiving = false;
			arrived = true;

		}
	}
	else {
		if (move_result.x<=0 && move_result.y<=0) {//超过但是没有接近目标坐标
			pos = nex_pos;
			pre_pos_idx++;
		}
	}
}
