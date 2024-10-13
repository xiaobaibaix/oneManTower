#pragma once

#include "Timer.h"
#include <functional>
#include <vector>
#include <SDL.h>

class Animation
{
public:
	Animation();
	~Animation()=default;

	void restart();

	void set_interval(double time);
	void set_texture(SDL_Texture* texture, int idx_width, int idx_group,std::vector<int> valid);
	void set_begin(int idx_begin);
	void set_callback(std::function<void()> callback);
	void set_is_loop(bool is_loop=true,int count_loot=-1);
	void set_width(int width);
	void set_play_dir(int dir = 1);//默认正方向
	void set_idx_callback(int idx);

	bool get_is_end();
	int get_begin();
	int get_idx_frame();
	double get_interval();
	int get_width();
	int get_idx_callback();

	void on_update(double delta_time);
	void on_draw(SDL_Renderer* render, const SDL_Point pos, double angle = 0);

private:
	Timer timer;

	bool is_loop = true;
	bool is_end = false;

	int count = 1;//循环次数
	int cur_count = 0;

	int dir = 1;

	int idx_frame = 0;
	int idx_width=0;
	int idx_begin=0;
	int idx_callback = 0;//属于idx_width范围;

	SDL_Texture* texture = nullptr;

	std::vector<SDL_Rect> tailor_rects;
	std::vector<int> idx_valid;//无效的下标

	std::function<void()> callback;
};



