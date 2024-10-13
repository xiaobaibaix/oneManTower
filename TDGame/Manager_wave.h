#pragma once

#include "Manager.h"
#include "Manager_config.h"

#include "Wave.h"
#include "Timer.h"

class Manager_wave :
    public Manager<Manager_wave>
{
    friend class Manager<Manager_wave>;
public:
    void set_wave_list(WaveList* wave_list);
    void set_cur_wave(Wave* wave);

    Wave* get_cur_wave();
    const WaveList& get_wave_list()const;
    int get_idx_cur_wave();
    Timer& get_time_wave();

    bool next_wave();

    void on_update(double delta_time);

protected:
    Manager_wave()=default;
    ~Manager_wave()=default;
private:
    Timer timer_wave;           //波次间隔时间计时器
    Timer timer_wave_evemt;     //波次内生成事件计时器

    bool is_set_wave = false;//是否已经设置了当前的波次
    bool is_generating = false;//是否真正生成对象

    Wave* cur_wave = nullptr;   //当前波次
    WaveList* wave_list=nullptr;//波次列表
};

