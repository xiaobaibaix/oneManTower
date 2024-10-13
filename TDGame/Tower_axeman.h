#pragma once
#include "Tower.h"
class Tower_axeman :
    public Tower
{
public:
    Tower_axeman(int idx_x, int idx_y);
    ~Tower_axeman();

    virtual void on_update(double delta_time)override;

    virtual bool fire(const Vector2D& dir)override;


};

