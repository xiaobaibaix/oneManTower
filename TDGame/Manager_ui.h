#pragma once
#include "Manager.h"

#include "Vector2D.h"

class Manager_ui:public Manager<Manager_ui>
{
	friend class Manager<Manager_ui>;
	friend class Manager_tower;
public:

	void on_input(const SDL_Event* event);
	void on_update(double delta_time);
	void on_draw(SDL_Renderer* render);

	void canLoseCoin(const Vector2D& pos);

protected:
	Manager_ui()=default;
	~Manager_ui()=default;

private:

	bool is_mouse_double_down = false;
	bool is_mouse_left_down = false;
	bool is_mouse_right_down = false;

	bool is_select_top = false;
	bool is_select_left = false;
	bool is_select_right = false;
	bool can_lose_coin = false;


	Vector2D tmp_pos;
	Vector2D mouse_pos;
	Vector2D mouse_idx_pos;
	Vector2D mouse_idx_pos_locked;

};

