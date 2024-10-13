#pragma once
#include "Bullet.h"
class Bullet_arrow :
    public Bullet
{
public:
    Bullet_arrow(const Vector2D& pos, const Vector2D& v);
    ~Bullet_arrow()=default;

    virtual void on_update(double delta_time)override;

    virtual void on_draw(SDL_Renderer* render)override;
    virtual void reset(const Vector2D& pos, const Vector2D& v)override;
private:
    double thta = 0;
};

