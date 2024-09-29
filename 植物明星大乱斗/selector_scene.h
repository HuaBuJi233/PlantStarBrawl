#ifndef _SELECTOR_SCENE_H_
#define _SELECTOR_SCENE_H_

#include <iostream>
#include "scene.h"
#include "scene_manager.h"

extern SceneManager scene_manager;

class SelectorScene :public Scene
{
public:
	SelectorScene() = default;
	~SelectorScene() = default;

	void on_enter()
	{
		std::cout << "#进入角色选择界面#" << std::endl;
	}
	void on_input(const ExMessage& msg)
	{
		if (msg.message == WM_KEYDOWN)
		{
			scene_manager.switch_to(SceneManager::SceneType::GAME);
		}
	}
	void on_update(int delay)
	{
		std::cout << "#更新角色选择界面#" << std::endl;
	}
	void on_draw()
	{
		outtextxy(0, 0, _T("角色选择场景"));
	}

	void on_exit()
	{
		std::cout << "#退出角色选择界面#" << std::endl;
	}
};

#endif // !_SELECTOR_SCENE_H_
