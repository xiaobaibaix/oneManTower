#pragma once
#include "Tower.h"
class Tower_archer :
    public Tower
{
public:
    Tower_archer(int idx_x, int idx_y);
    ~Tower_archer();

    virtual void on_update(double delta_time)override;

    virtual bool fire(const Vector2D& dir)override;


};

