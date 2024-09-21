#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_

#include <iostream>
#include "scene.h"
#include "scene_manager.h"

extern SceneManager scene_manager;

class GameScene :public Scene
{
public:
	GameScene() = default;
	~GameScene() = default;

	void on_enter()
	{
		std::cout << "#������Ϸ����#" << std::endl;
	}
	void on_input(const ExMessage& msg)
	{
		if (msg.message == WM_KEYDOWN)
		{
			scene_manager.switch_to(SceneManager::SceneType::MENU);
		}
	}
	void on_update()
	{
		std::cout << "#������Ϸ����#" << std::endl;
	}
	void on_draw()
	{
		outtextxy(0, 0, _T("��Ϸ����"));
	}
	void on_exit()
	{
		std::cout << "#�˳���Ϸ����#" << std::endl;
	}
};

#endif // !_GAME_SCENE_H_

