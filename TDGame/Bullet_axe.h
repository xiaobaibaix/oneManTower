#pragma once
#include "Bullet.h"
class Bullet_axe :
    public Bullet
{
public:
    Bullet_axe(const Vector2D& pos,const Vector2D& v);
    ~Bullet_axe()=default;

    virtual void on_update(double delta_time)override;

    virtual void reset(const Vector2D& pos, const Vector2D& v);

private:



};

