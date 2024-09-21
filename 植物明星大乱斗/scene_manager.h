#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_

#include "scene.h"

extern Scene* menu_scene;
extern Scene* game_scene;
extern Scene* selector_scene;

class SceneManager
{
public:
	//��������ö��
	enum class SceneType//ǿ����ö�٣������ϸ������
	{
		MENU = 0,
		GAME,
		SELECTOR
	};
public:
	SceneManager() = default;
	~SceneManager() = default;

	void set_current_scene(Scene* scene)//���õ�ǰ����
	{
		current_scene = scene;
		current_scene->on_enter();
	}
	void switch_to(SceneType type)//�л�����
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
