#pragma once

#include "Manager.h"
#include "Enemy.h"
#include "Wave.h"
#include "Timer.h"
#include "EnemyType.h"


#include <list>

class Manager_enemy :
    public Manager<Manager_enemy>
{
    friend class Manager<Manager_enemy>;
public:

    void generate_enemy(EnemyType type,Route* route);

    bool is_not_enemy();
    void set_callback(std::function<void()> callback);

    const std::list<Enemy*>& get_enemys_list()const;
    void on_collision();

    void on_update(double delta_time);
    void on_draw(SDL_Renderer* render);
protected:
    Manager_enemy()=default;
    ~Manager_enemy()= default;
private:
    int enemy_count = 0;

    std::function<void()> callback_end;

    std::list<Enemy*> enemys_list;
};

