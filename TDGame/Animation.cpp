#include "Animation.h"
#include <iostream>

Animation::Animation()
{
	timer.set_shot();//默认循环
	timer.set_callback([&]() {
		if (callback&&idx_frame==idx_callback)callback();
		if (is_loop) {
			idx_frame++;
			if (idx_frame >= idx_width)idx_frame= 0;
			for (int i = 0; i < idx_valid.size(); i++) {
				if (idx_frame + idx_begin== idx_valid.at(i)) {
					idx_frame = 0;
					break;
				}
			}
		}
		else if (!is_loop && cur_count < count) {//不无限循环
			idx_frame++;
			for (int i = 0; i < idx_valid.size(); i++) {
				if (idx_frame + idx_begin == idx_valid.at(i)) {
					idx_frame = 0;
					cur_count++;
					if (cur_count == count)is_end = true;
					return;
				}
			}
			if (idx_frame >= idx_width) {
				idx_frame = 0;
				cur_count++;
				if (cur_count == count)is_end = true;
				return;
			}
		}
	});


}

void Animation::set_interval(double time)
{
	timer.set_wait_time(time);
}

void Animation::set_texture(SDL_Texture* texture, int width, int group, std::vector<int> valid)
{
	if (!texture)
		return;
	this->texture = texture;

	int set_x,set_y;
	SDL_QueryTexture(texture, nullptr, nullptr, &set_x, &set_y);

	idx_valid= valid;//无效的下标
	idx_width = width;
	idx_callback = width;//回调函数的调用下标

	const int frame_w = set_x / width;
	const int frame_h = set_y / group;
	tailor_rects.resize(width * group);
	for (int y = 0; y < group;y++) {
		for (int x = 0; x < width;x++) {
			SDL_Rect& idx_rect = tailor_rects.at(y * width + x);
			idx_rect = {
				x* frame_w,y*frame_h,
				frame_w,frame_h
			};
		}
	}
}

void Animation::restart()
{
	idx_frame = 0;
	cur_count = 0;
	is_end = false;
	timer.restart();
}

void Animation::set_begin(int idx_begin)
{
	this->idx_begin = idx_begin;
}

void Animation::set_callback(std::function<void()> callback)
{
	this->callback = callback;
}

void Animation::set_is_loop(bool is_loop,int count_loop)
{
	this->is_loop = is_loop;
	timer.set_shot(idx_width);
	count = count_loop;
	restart();
}

void Animation::set_width(int width)
{
	this->idx_width = width;
}

void Animation::set_play_dir(int dir)
{
	this->dir = dir;
}

void Animation::set_idx_callback(int idx)
{
	idx_callback = idx;
}


bool Animation::get_is_end()
{
	return is_end;
}

int Animation::get_begin()
{
	return idx_begin;
}

int Animation::get_idx_frame()
{
	return idx_frame;
}

double Animation::get_interval()
{
	return timer.get_wait_time();
}

int Animation::get_width()
{
	return idx_width;
}

int Animation::get_idx_callback()
{
	return idx_callback;
}

void Animation::on_update(double delta_time)
{
	if(!is_end)timer.on_update(delta_time);
}

void Animation::on_draw(SDL_Renderer* render, const SDL_Point pos, double angle)
{
	if (is_end)return;
	const int idx_frame_ = (dir == 1) ? idx_frame : idx_width- idx_frame -1;
	const SDL_Rect& srcrect = tailor_rects.at(idx_frame_ + idx_begin);
	const SDL_Rect dstrect = {pos.x,pos.y,srcrect.w,srcrect.h};
	SDL_RenderCopyEx(render, texture, &srcrect, &dstrect, angle, nullptr, SDL_RendererFlip::SDL_FLIP_NONE);
}

