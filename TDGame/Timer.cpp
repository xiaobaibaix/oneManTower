#include "Timer.h"
#include <iostream>
//����
void Timer::restart() {
	pass_time = 0;
	count_shotted = 0;
	paused = false;
}
bool Timer::is_finish()
{
	return count_shotted==count?true:false;
}
void Timer::set_wait_time(double val) {
	wait_time = val;
}
void Timer::set_shot(int count) {
	this->count = count;
}
void Timer::set_callback(std::function<void()> callback) {
	this->callback = callback;
}

void Timer::reset_pass_time()
{
	pass_time = 0;
}

int Timer::get_count_shotted()
{
	return count_shotted;
}
bool Timer::get_isPause()//�Ƿ���ͣ
{
	return paused;
}
double Timer::get_wait_time()
{
	return wait_time;
}
//��ͣ
void Timer::pause() {
	this->paused = true;
}
//����
void Timer::resume() {
	this->paused = false;
}
void Timer::on_update(double delta) {
	if (this->paused)
		return;
	pass_time += delta;
	if (count<=0) {//���޴���
		if (pass_time > wait_time) {
			if(callback){
				callback();
			}
			//pass_time = pass_time - wait_time;
			pass_time = 0;
		}
	}
	else {
		if (pass_time > wait_time) {
			if (count_shotted < count) {
				count_shotted++;
				if (callback) {
					callback();
				}
				//pass_time = pass_time - wait_time;
				pass_time = 0;
			}
			else {
				//std::cout << "��ʱ����" << std::endl;
				pause();//��ͣ
			}
		}
	}
}
