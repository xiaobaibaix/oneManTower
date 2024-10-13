#pragma once
#include "Enemy.h"
class Enemy_goblinPriest :
    public Enemy
{
public:
    Enemy_goblinPriest(const Vector2D& pos, int dir);
    ~Enemy_goblinPriest();

    void on_update(double delta_time)override;
    void on_draw(SDL_Renderer* render)override;
};

