#pragma once
#include "Tower.h"
class Tower_gunner :
    public Tower
{
public:
    Tower_gunner(int idx_x,int idx_y);
    ~Tower_gunner();

    virtual void on_update(double delta_time)override;

    virtual bool fire(const Vector2D& dir)override;
};

