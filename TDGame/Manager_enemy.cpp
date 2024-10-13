#include "Manager_enemy.h"

#include "Enemy_slime.h"
#include "Enemy_goblin.h"
#include "Enemy_goblinPriest.h"
#include "Enemy_kingSlim.h"
#include "Enemy_skeleton.h"

#include "Tower.h"

#include "Bullet.h"

#include "Manager_config.h"
#include "Manager_tower.h"
#include "Manager_wave.h"
#include "Manager_game.h"

#include "Vector2D.h"
#include "Route.h"

bool Manager_enemy::is_not_enemy()
{
	return (enemys_list.size() == 0) ? true : false;
}

void Manager_enemy::set_callback(std::function<void()> callback)
{
	this->callback_end = callback;
}

const std::list<Enemy*>& Manager_enemy::get_enemys_list() const
{
	return enemys_list;
}

void Manager_enemy::on_collision()
{
	static const std::vector<Tower*>& tower_list = Manager_tower::instance()->getTowerList();

	for (auto& tower:tower_list) {
		const std::vector<Bullet*>& bullet_list=tower->getBulletList();
		for (auto& bullet : bullet_list) {
			for (auto& enemy: enemys_list) {
				if (enemy->get_enemy_is_living()&&bullet->on_collision(enemy)) {
					std::cout<< "enemy: " << enemy->getHP() << " hit damage: " << bullet->getDamage() << std::endl;
					enemy->decHP(bullet->getDamage());
					bullet->setHitEnemy(enemy);
					//if (enemy->getHP() <= 0)enemy->die();
				}
			}
		}
	}
}

void Manager_enemy::generate_enemy(EnemyType type,Route* route)
{
	if (!route)return;

	const SDL_Point& brith_place = *route->get_idx_list().begin();
	int dir = (int)Manager_config::instance()->map.get_tile_map().at(brith_place.y).at(brith_place.x).direction;

	switch (type)
	{
	case EnemyType::Slim:
		enemys_list.push_back(new Enemy_slime({ (float)(brith_place .x),(float)(brith_place .y) }, dir));
		break;
	case EnemyType::KingSlim:
		enemys_list.push_back(new Enemy_kingSlim({ (float)(brith_place.x),(float)(brith_place.y) }, dir));
		break;
	case EnemyType::Skeleton:
		enemys_list.push_back(new Enemy_skeleton({ (float)(brith_place.x),(float)(brith_place.y) }, dir));
		break;
	case EnemyType::Goblin:
		enemys_list.push_back(new Enemy_goblin({ (float)(brith_place.x),(float)(brith_place.y) }, dir));
		break;
	case EnemyType::GoblinPriest:
		enemys_list.push_back(new Enemy_goblinPriest({ (float)(brith_place.x),(float)(brith_place.y) }, dir));
		break;
	default:
		return;
	}

	enemys_list.back()->set_route(route);
}

void Manager_enemy::on_update(double delta_time)
{
	if (enemys_list.size() == 0)if(callback_end)callback_end();
	for (std::list<Enemy*>::iterator it = enemys_list.begin(); it != enemys_list.end();) {
		Enemy* enemy = *it;
		if (enemy->get_enemy_is_arrived())enemy->die();
		if (!enemy->get_enemy_is_living()) {
			it=enemys_list.erase(it);
			continue;
		}
		enemy->on_update(delta_time);
		++it;
	}

	on_collision();
}

void Manager_enemy::on_draw(SDL_Renderer* render)
{
	for (auto& enemy : enemys_list) {
		if(enemy&&enemy->get_enemy_is_living())enemy->on_draw(render);
	}
}



