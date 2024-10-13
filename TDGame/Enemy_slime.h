#pragma once
#include "Enemy.h"
class Enemy_slime :
    public Enemy
{
public:
    Enemy_slime(const Vector2D& pos, int dir);
    ~Enemy_slime();

    void on_update(double delta_time)override;
    void on_draw(SDL_Renderer* render)override;

private:

};

