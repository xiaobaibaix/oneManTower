#include "Tower.h"
#include "Manager_enemy.h"
#include "Manager_game.h"

Tower::Tower()
{
	timer_fire.set_shot(1);
	timer_fire.set_callback([&]() {can_fire = true;});
	timer_fire.pause();//��ͣ

	anim.set_is_loop(true);
}

void Tower::on_update(double delta_time)
{
	timer_fire.on_update(delta_time);
	anim.on_update(delta_time);

	for (Bullet*& bullet : bullet_list)
		bullet->on_update(delta_time);

	if (!lose_target) {//û��ʧȥĿ��
		Vector2D distence = (locked_target->getPos() - pos);
		dir = distence / distence.getMode_length();

		if (can_fire) {//���Կ���
			std::cout << "fire" << std::endl;
			if (fire(dir)) {
				//�����ӵ�����
				timer_fire.restart();
				can_fire = false;
			}
		}
		//����Ƿ񳬳���Χ
		//std::cout << locked_target->getPos().x << locked_target->getPos().y << std::endl;
		if (!locked_target->get_enemy_is_living() || !inViewRange(locked_target->getPos())){
			lose_target = true;
			std::cout << "lose enemy!" << std::endl;
		}
	}
	if(lose_target) {//ʧȥĿ��
		//Ѱ��Ŀ��
		static const std::list<Enemy*>& enemy_list = Manager_enemy::instance()->get_enemys_list();
		for (auto& enemy:enemy_list) {
			if (inViewRange(enemy->getPos())) {
				locked_target = enemy;
				lose_target = false;
				std::cout << "lock enemy!" << std::endl;
				break;
			}
		}
	}

}

void Tower::on_draw(SDL_Renderer* render)
{
	//������Ⱦ
	anim.on_draw(render, {(int)pos.x*SIZE_TILE,(int)pos.y*SIZE_TILE });

	//�ӵ���Ⱦ
	for (Bullet*& bullet : bullet_list)
		bullet->on_draw(render);

	//����ǰ�ȼ�
	static SDL_Texture* tex_grades[] = {
		Manager_resources::instance()->get_texture_pool().find(ResID::Tex_UINumber1)->second,
		Manager_resources::instance()->get_texture_pool().find(ResID::Tex_UINumber2)->second,
		Manager_resources::instance()->get_texture_pool().find(ResID::Tex_UINumber3)->second,
		Manager_resources::instance()->get_texture_pool().find(ResID::Tex_UINumber4)->second,
		Manager_resources::instance()->get_texture_pool().find(ResID::Tex_UINumber5)->second,
		Manager_resources::instance()->get_texture_pool().find(ResID::Tex_UINumber6)->second,
		Manager_resources::instance()->get_texture_pool().find(ResID::Tex_UINumber7)->second,
		Manager_resources::instance()->get_texture_pool().find(ResID::Tex_UINumber8)->second,
		Manager_resources::instance()->get_texture_pool().find(ResID::Tex_UINumber9)->second,
	};

	SDL_Rect tex_grade_rect = { pos.x* SIZE_TILE,pos.y* SIZE_TILE +(SIZE_TILE/4)*3,SIZE_TILE/4,SIZE_TILE/4 };
	SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
	if (this->idx_grade<9) {
		SDL_RenderDrawRect(render, &tex_grade_rect);
		SDL_RenderCopyEx(render, tex_grades[this->idx_grade], nullptr, &tex_grade_rect, 0, nullptr, SDL_RendererFlip::SDL_FLIP_NONE);
	}

	//��������ͷ
	static SDL_Texture* tex_update = Manager_resources::instance()->get_texture_pool().find(ResID::Tex_UIUpdate)->second;
	static const int& cion = Manager_game::instance()->get_coin_count();

	if (idx_grade<8&& cion>=this->upgrade_cost[idx_grade+1]) {
		const SDL_Rect tex_update_rect = { pos.x*SIZE_TILE + SIZE_TILE / 2 - SIZE_TILE / 8,pos.y* SIZE_TILE,SIZE_TILE / 4,SIZE_TILE / 4 };
		SDL_RenderCopyEx(render, tex_update, nullptr, &tex_update_rect, 0, nullptr, SDL_RendererFlip::SDL_FLIP_NONE);
	}

}

bool Tower::addGrade()
{
	if (idx_grade >7) return false;
	idx_grade++;
	timer_fire.set_wait_time(interval[idx_grade]);
	return true;
}

const Vector2D& Tower::getPos() const
{
	return pos;
}

double Tower::getViewRange()
{
	return view_range[idx_grade];
}

const std::vector<Bullet*>& Tower::getBulletList() const
{
	return bullet_list;
}

bool Tower::fire(const Vector2D& dir)
{
	if (!(anim.get_idx_frame() == anim.get_idx_callback()))return false;
	for (auto& bullet : bullet_list) {
		if (bullet->isRemove()&& !bullet->isValid()) {//���Ƴ�����Ч
			bullet->reset(pos * SIZE_TILE, dir * bullet_speed);
			//std::cout << "reset bullet!" << std::endl;
			return true;
		}
	}
	return false;
	//std::cout << "new bullet!" << std::endl;
}

void Tower::setSelect(bool flag)
{
}

bool Tower::getSelect()
{
	return false;
}

bool Tower::inViewRange(const Vector2D& pos)
{
	const double target_distence = (pos*SIZE_TILE - this->pos*SIZE_TILE).getMode_length();
	if (target_distence <= view_range[idx_grade]*SIZE_TILE)
		return true;
	else 
		return false;
}
