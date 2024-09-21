#include <iostream>
#include <windows.h>
#include <graphics.h>
#include "menu_scene.h"
#include "game_scene.h"
#include "selector_scene.h"
#include "scene_manager.h"

Scene* menu_scene = nullptr;
Scene* game_scene = nullptr;
Scene* selector_scene = nullptr;
SceneManager scene_manager;

int main()
{
	ExMessage msg;
	const int FPS = 60;

	initgraph(1280, 720);
	BeginBatchDraw();//暂停输出，将窗口缓存

	menu_scene = new MenuScene();
	game_scene = new GameScene();
	selector_scene = new SelectorScene();

	scene_manager.set_current_scene(menu_scene);//初始化:场景管理器 → menu_scene
	while (true)
	{
		DWORD frame_star_time = GetTickCount();

		while (peekmessage(&msg))
		{
			scene_manager.on_input(msg);
		}
		scene_manager.on_update();
		cleardevice();//使用背景色清空窗口
		scene_manager.on_draw();
		FlushBatchDraw();//输出缓存窗口

		DWORD frame_end_time = GetTickCount();
		DWORD frame_delete_time = frame_end_time - frame_star_time;
		if (frame_delete_time < 1000 / FPS)
			Sleep(1000 / FPS - frame_delete_time);
	}
	EndBatchDraw();
	return 0;
}