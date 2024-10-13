#pragma once
#include <functional>


class Timer
{
public:
	Timer() = default;
	~Timer() = default;
public:
	void set_wait_time(double val);
	void set_shot(int count=-1);//Ĭ�����޴���
	void set_callback(std::function<void()> callback);
	void reset_pass_time();

	int get_count_shotted();//�õ��������Ĵ���
	bool get_isPause();
	double get_wait_time();

	void pause();
	void resume();
	void restart();

	bool is_finish();

	void on_update(double delta);
private:
	double pass_time = 0;			//������ʱ��
	double wait_time = 0;			//ʱ����
	bool paused = false;			//�Ƿ���ͣ
	//bool isFinish = false;			//�Ƿ��ʱ����
	int count_shotted = 0;			//����������
	int count = -1;					//��������-1������,
	std::function<void()> callback;	//�ص�����
};



