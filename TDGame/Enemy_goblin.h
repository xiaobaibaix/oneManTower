#pragma once
#include "Enemy.h"
class Enemy_goblin :
    public Enemy
{
public:
    Enemy_goblin(const Vector2D& pos, int dir);
    ~Enemy_goblin();

    void on_update(double delta_time)override;
    void on_draw(SDL_Renderer* render)override;
};

