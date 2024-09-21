#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_

#include "scene.h"

extern Scene* menu_scene;
extern Scene* game_scene;
extern Scene* selector_scene;

class SceneManager
{
public:
	//场景类型枚举
	enum class SceneType//强作用枚举，更加严格的限制
	{
		MENU = 0,
		GAME,
		SELECTOR
	};
public:
	SceneManager() = default;
	~SceneManager() = default;

	void set_current_scene(Scene* scene)//设置当前场景
	{
		current_scene = scene;
		current_scene->on_enter();
	}
	void switch_to(SceneType type)//切换场景
	{
		current_scene->on_exit();
		switch (type)
		{
		case SceneType::MENU:
			current_scene = menu_scene;
			break;
		case SceneType::GAME:
			current_scene = game_scene;
			break;
		case SceneType::SELECTOR:
			current_scene = selector_scene;
		default:
			break;
		}
		current_scene->on_enter();
	}
	void on_input(const ExMessage& msg)
	{
		current_scene->on_input(msg);
	}
	void on_update()
	{
		current_scene->on_update();
	}
	void on_draw()
	{
		current_scene->on_draw();
	}
private:
	Scene* current_scene = nullptr;
};

#endif // !_SCENE_MANAGER_H_
