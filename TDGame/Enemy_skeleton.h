#pragma once
#include "Enemy.h"
class Enemy_skeleton :
    public Enemy
{
public:

    Enemy_skeleton(const Vector2D& pos, int dir);
    ~Enemy_skeleton();

    void on_update(double delta_time)override;
    void on_draw(SDL_Renderer* render)override;
};

