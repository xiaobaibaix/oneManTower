#pragma once
#include "Vector2D.h"
#include "Animation.h"
#include "Timer.h"
#include "Manager_config.h"
#include "Manager_resources.h"
#include "Bullet_axe.h"
#include "Enemy.h"

class Tower
{
public:
	friend class Manager_tower;
public:
	Tower();
	virtual~Tower() = default;

	virtual void on_update(double delta_time);
	virtual void on_draw(SDL_Renderer* render);

	bool addGrade();//����
	const Vector2D& getPos()const;
	double getViewRange();
	const std::vector<Bullet*>& getBulletList()const;
	
	virtual bool fire(const Vector2D& dir);

	void setSelect(bool flag);
	bool getSelect();
protected:
	//ģ����Ϣ
	double const* interval = nullptr;	//����ʱ����
	double const* damage = nullptr;		//�����˺�
	double const* view_range = nullptr;	//��Ұ��Χ
	double const* cost = nullptr;		//���컨��
	double const* upgrade_cost =nullptr;//��������

	double bullet_speed = 0;//�ӵ��ƶ����ٶ�
	
	bool can_fire = true;//�Ƿ���Կ���
	bool lose_target = true;//Ŀ���Ƿ�ʧ

	int idx_grade = 0;//�ȼ��±�
	
	Enemy* locked_target =nullptr;//�������ĵ���

	Timer timer_fire;//����ʱ��

	Animation anim;//����

	Vector2D pos;//��������
	Vector2D dir;//�泯��

	std::vector<Bullet*> bullet_list;

private:
	bool inViewRange(const Vector2D& pos);
};

