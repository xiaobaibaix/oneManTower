#pragma once
#include <functional>


class Timer
{
public:
	Timer() = default;
	~Timer() = default;
public:
	void set_wait_time(double val);
	void set_shot(int count=-1);//默认无限触发
	void set_callback(std::function<void()> callback);
	void reset_pass_time();

	int get_count_shotted();//得到被触发的次数
	bool get_isPause();
	double get_wait_time();

	void pause();
	void resume();
	void restart();

	bool is_finish();

	void on_update(double delta);
private:
	double pass_time = 0;			//经过的时间
	double wait_time = 0;			//时间间隔
	bool paused = false;			//是否暂停
	//bool isFinish = false;			//是否计时结束
	int count_shotted = 0;			//被触发次数
	int count = -1;					//触发次数-1无数次,
	std::function<void()> callback;	//回调函数
};



