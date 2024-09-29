#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_

#include <iostream>
#include "scene.h"
#include "scene_manager.h"
#include "animation.h"
#include "camera.h"

extern SceneManager scene_manager;
/*
* 动画类和相机类测试
extern Atlas atlas_peashooter_idle_right;	//豌豆射手向右动画
*/

class GameScene :public Scene
{
public:
	GameScene() = default;
	~GameScene() = default;

	void on_enter()
	{
		/*
		* 动画类和相机类测试
		test.set_atlas(&atlas_peashooter_idle_right);
		test.set_loop(true);
		test.set_interval(60);
		camera_test.init_camera(100, 100);
		/*test.set_callback(
			[]()
			{
				scene_manager.switch_to(SceneManager::SceneType::MENU);
			}
		);*/
	}
	void on_input(const ExMessage& msg)
	{
		if (msg.message == WM_KEYDOWN)
		{
			scene_manager.switch_to(SceneManager::SceneType::MENU);
		}
	}
	void on_update(int delay)
	{
		/*
		* 动画类和相机类测试
		animation_test.on_update(delay);
		camera_test.on_update(delay);
		*/
		std::cout << "#更新游戏界面#" << std::endl;
	}
	void on_draw()
	{
		/*
		* 动画类和相机类测试
		Vector2 new_pos = camera_test.get_position();
		animation_test.on_draw(100 - new_pos.x, 100 - new_pos.y);;
		*/
		outtextxy(0, 0, _T("游戏场景"));
	}
	void on_exit()
	{
		std::cout << "#退出游戏界面#" << std::endl;
	}
private:
	/*
	* 动画类和相机类测试
	Animation animation_test;
	Camera camera_test;
	*/
};

#endif // !_GAME_SCENE_H_
