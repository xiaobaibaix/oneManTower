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
    Timer timer_wave;           //���μ��ʱ���ʱ��
    Timer timer_wave_evemt;     //�����������¼���ʱ��

    bool is_set_wave = false;//�Ƿ��Ѿ������˵�ǰ�Ĳ���
    bool is_generating = false;//�Ƿ��������ɶ���

    Wave* cur_wave = nullptr;   //��ǰ����
    WaveList* wave_list=nullptr;//�����б�
};

