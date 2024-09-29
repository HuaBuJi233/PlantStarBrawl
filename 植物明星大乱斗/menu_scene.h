#ifndef _MENU_SCENE_H_
#define _MENU_SCENE_H_

#include <iostream>
#include "scene.h"
#include "scene_manager.h"

extern SceneManager scene_manager;

class MenuScene :public Scene
{
public:
	MenuScene() = default;
	~MenuScene() = default;

	void on_enter()
	{
		std::cout << "#进入菜单界面#" << std::endl;
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
		std::cout << "#更新菜单界面#" << std::endl;
	}
	void on_draw()
	{
		outtextxy(0, 0, _T("主菜单场景"));
	}

	void on_exit()
	{
		std::cout << "#退出菜单界面#" << std::endl;
	}
private:
};

#endif // !_MENU_SCENE_H_
