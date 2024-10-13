#pragma once
#include "Bullet.h"
#include "Vector2D.h"

class Bullet_shell :
    public Bullet
{
public:
    Bullet_shell(const Vector2D& pos, const Vector2D& v);
    ~Bullet_shell() = default;


    virtual void on_update(double delta_time)override;
    virtual void on_draw(SDL_Renderer* render)override;



    virtual void reset(const Vector2D& pos, const Vector2D& v);
private:
    int hit_range = 0;

    double spurting = 0;///Ω¶…‰…À∫¶±»

    Animation ainm_explode;//±¨’®∂Øª≠

private:
    bool in_hit_range(const Vector2D& srcpos, float idx_r);//¡Ω∏ˆ‘≤
};

