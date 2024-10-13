#pragma once
#include "Enemy.h"
class Enemy_kingSlim :
    public Enemy
{
public:
    Enemy_kingSlim(const Vector2D& pos, int dir);
    ~Enemy_kingSlim();

    void on_update(double delta_time)override;
    void on_draw(SDL_Renderer* render)override;
};

