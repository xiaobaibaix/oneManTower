#include "Manager_wave.h"
#include "Manager_config.h"
#include "Manager_enemy.h"
#include "Manager_game.h"

void Manager_wave::set_wave_list(WaveList* wave_list)
{
	this->wave_list = wave_list;

	static Manager_config* config = Manager_config::instance();

	if (wave_list && wave_list->size() > 0) {//�����б�����б�Ϊ��!
		//���õ�һ��
		cur_wave = &this->wave_list->at(0);

		timer_wave.set_wait_time(cur_wave->interval);//��һ���Ŀ�ʼʱ��
		timer_wave.set_shot(this->wave_list->size());//���������б��ȴ�

		Manager_game::instance()->add_coin(cur_wave->rewards);

		timer_wave.set_callback([&]() {//��ʱ���Ļص�����
			std::cout << "���ο�ʼ" << std::endl;
			is_generating = true;
			timer_wave_evemt.restart();
			timer_wave_evemt.set_shot(cur_wave->spawn_event_list.size());
			timer_wave_evemt.set_wait_time(cur_wave->spawn_event_list.at(0).interval);
			timer_wave_evemt.set_callback([&]() {
				//���ɵ���
				const EnemyType& type = cur_wave->spawn_event_list.at(timer_wave_evemt.get_count_shotted() - 1).enemy_type;
				auto& route= config->map.get_route_pool()->at(cur_wave->spawn_event_list[timer_wave_evemt.get_count_shotted()-1].spawn_point);
				Manager_enemy::instance()->generate_enemy(type,&route);
				if (timer_wave_evemt.is_finish()) {
					is_generating = false;
					cur_wave = nullptr;
				}
				}
			);
			timer_wave.pause();//�ر��ⲿ��ʱ��
			}
		);
		Manager_enemy::instance()->set_callback([&]() {next_wave();});
	}

}

Wave* Manager_wave::get_cur_wave()
{
	return cur_wave;
}

const WaveList& Manager_wave::get_wave_list() const
{
	return *wave_list;
}

int Manager_wave::get_idx_cur_wave()
{
	return timer_wave.get_count_shotted();
}

Timer& Manager_wave::get_time_wave()
{
	return timer_wave;
}

bool Manager_wave::next_wave()
{
	if (timer_wave.is_finish()||cur_wave)return false;
	cur_wave =&wave_list->at(timer_wave.get_count_shotted());
	Manager_game::instance()->add_coin(cur_wave->rewards);
	timer_wave.set_wait_time(cur_wave->interval);
	timer_wave.resume();//�����ⲿ��ʱ��
	return true;
}

void Manager_wave::set_cur_wave(Wave* wave)
{
	cur_wave = wave;
}

void Manager_wave::on_update(double delta_time)
{
	timer_wave.on_update(delta_time);
	timer_wave_evemt.on_update(delta_time);

}

