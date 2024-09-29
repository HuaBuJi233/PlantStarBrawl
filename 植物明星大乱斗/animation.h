#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include <functional>
#include "atlas.h"
#include "util.h"
#include <iostream>

class Animation
{
public:
	Animation() = default;
	~Animation() = default;

	void on_reset()
	{
		index = 0;
		timer = 0;
	}
	void set_atlas(Atlas* ats)
	{
		on_reset();
		atlas = ats;
	}
	void set_loop(bool flag)
	{
		is_loop = flag;
	}
	void set_interval(int ms)
	{
		interval = ms;
	}
	void on_update(int delay)
	{
		timer += delay;
		if (timer >= interval)
		{
			index++;
			timer = 0;
			if (index >= atlas->get_size())
				index = is_loop ? 0 : atlas->get_size() - 1;
			//std::cout << "第 " << index << " 帧" << std::endl;
			if (check_finished() && !is_loop && callback)
				callback();
		}
	}
	void on_draw(int x, int y) const
	{
		putimage_alpha(x, y, atlas->get_image(index));
	}
	int get_index_frame()
	{
		return index;
	}
	IMAGE* get_frame(int idx)
	{
		return atlas->get_image(idx);
	}
	bool check_finished()
	{
		if (is_loop) return false;
		return (index == atlas->get_size() - 1);
	}
	void set_callback(std::function<void()> callback)//设置回调函数
	{
		this->callback = callback;
	}
private:
	int index = 0;
	int timer = 0;
	int interval = 0;
	bool is_loop = true;
	Atlas* atlas = nullptr;
	std::function<void()> callback;
};

#endif