#include <iostream>
#include <windows.h>
#include <graphics.h>
#include "scene_manager.h"
#include "util.h"
#include "menu_scene.h"
#include "game_scene.h"
#include "selector_scene.h"
#include "atlas.h"

#pragma comment(lib, "Winmm.lib")


//��Ϸ����
Scene* menu_scene = nullptr;
Scene* game_scene = nullptr;
Scene* selector_scene = nullptr;
SceneManager scene_manager;

//ͼƬ��Դ
// 1.���˵�����
IMAGE img_menu_background;										// ���˵�����ͼƬ
// 2.ѡ�ǽ������ԴͼƬ
IMAGE img_VS;													// VS ������ͼƬ
IMAGE img_1P;													// 1P �ı�ͼƬ
IMAGE img_2P;													// 2P �ı�ͼƬ
IMAGE img_1P_desc;												// 1P ��λ����ͼƬ
IMAGE img_2P_desc;												// 2P ��λ����ͼƬ
IMAGE img_gravestone_left;										// �������Ĺ��ͼƬ
IMAGE img_gravestone_right; 									// �����ҵ�Ĺ��ͼƬ
IMAGE img_selector_tip; 										// ѡ�ǽ�����ʾ�ı�ͼƬ
IMAGE img_selector_background;									// ѡ�ǽ��汳��ͼƬ
IMAGE img_1P_selector_btn_idle_left; 							// 1P ����ѡ��ťĬ��״̬ͼƬ
IMAGE img_1P_selector_btn_idle_right;							// 1P ����ѡ��ťĬ��״̬ͼƬ
IMAGE img_1P_selector_btn_down_left;							// 1P ����ѡ��ť����״̬ͼƬ
IMAGE img_1P_selector_btn_down_right;							// 1P ����ѡ��ť����״̬ͼƬ
IMAGE img_2P_selector_btn_idle_left;							// 2P ����ѡ��ťĬ��״̬ͼƬ
IMAGE img_2P_selector_btn_idle_right;							// 2P ����ѡ��ťĬ��״̬ͼƬ
IMAGE img_2P_selector_btn_down_left;							// 2P ����ѡ��ť����״̬ͼƬ
IMAGE img_2P_selector_btn_down_right;							// 2P ����ѡ��ť����״̬ͼƬ
IMAGE img_peashooter_selector_background_left;					// ѡ�ǽ��泯����������ֱ���ͼƬ
IMAGE img_peashooter_selector_background_right;					// ѡ�ǽ��泯���ҵ������ֱ���ͼƬ
IMAGE img_sunflower_selector_background_left;					// ѡ�ǽ��泯��������տ�����ͼƬ
IMAGE img_sunflower_selector_background_right;					// ѡ�ǽ��泯���ҵ����տ�����ͼƬ
// 3.��Ϸ�������Դ ͼƬ
IMAGE img_sky;													// ���ͼƬ
IMAGE img_hills;												// ɽ��ͼƬ
IMAGE img_platform_large;										// ����ƽ̨ͼƬ
IMAGE img_platform_small;										// С��ƽ̨ͼƬ
IMAGE img_1P_cursor;											// 1P ָʾ���ͼƬ
IMAGE img_2P_cursor;											// 2P ָʾ���ͼƬ
// 4.��Ϸ(ս��)�����ɫ�ĵ���Դ ͼ��
Atlas atlas_peashooter_idle_left;								// �����ֳ������Ĭ�϶���ͼ��
Atlas atlas_peashooter_idle_right;								// �����ֳ����ҵ�Ĭ�϶���ͼ��
Atlas atlas_peashooter_run_left;								// �����ֳ�������ܲ�����ͼ��
Atlas atlas_peashooter_run_right;								// �����ֳ����ҵ��ܲ�����ͼ��
Atlas atlas_peashooter_attack_ex_left;							// �����ֳ�����Ĺ�������ͼ��
Atlas atlas_peashooter_attack_ex_right;							// �����ֳ����ҵĹ�������ͼ��
Atlas atlas_peashooter_die_left;								// �����ֳ��������������ͼ��
Atlas atlas_peashooter_die_right;								// �����ֳ����ҵ���������ͼ��
Atlas atlas_sunflower_idle_left;								// ���տ��������Ĭ�϶���ͼ��
Atlas atlas_sunflower_idle_right;								// ���տ������ҵ�Ĭ�϶���ͼ��
Atlas atlas_sunflower_run_left;									// ���տ���������ܲ�����ͼ��
Atlas atlas_sunflower_run_right;								// ���տ������ҵ��ܲ�����ͼ��
Atlas atlas_sunflower_attack_ex_left;							// ���տ�������Ĺ�������ͼ��
Atlas atlas_sunflower_attack_ex_right;							// ���տ������ҵĹ�������ͼ��
Atlas atlas_sunflower_die_left;									// ���տ����������������ͼ��
Atlas atlas_sunflower_die_right;								// ���տ������ҵ���������ͼ��
// 5.��Ϸ(ս��)������������Դ ͼ��
IMAGE img_pea;													// �㶹ͼƬ
Atlas atlas_pea_break;											// �㶹���鶯��ͼ��
Atlas atlas_sun;												// �չ⶯��ͼ��
Atlas atlas_sun_explode;										// �չⱬը����ͼ��
Atlas atlas_sun_ex;												// �����չ⶯��ͼ��
Atlas atlas_sun_ex_explode;										// �����չⱬը����ͼ��
Atlas atlas_sun_text;											// ���ա� �ı�����ͼ��
Atlas atlas_run_effect;											// ������Ч����ͼ��
Atlas atlas_jump_effect;										// ��Ծ��Ч����ͼ��
Atlas atlas_land_effect;										// �����Ч����ͼ��
// 6.��Ϸ�����������Դ ͼ��
IMAGE img_1P_winner;											// 1P ��ʤ�ı�ͼƬ
IMAGE img_2P_winner;											// 2P ��ʤ�ı�ͼƬ
IMAGE img_winner_bar;											// ��ʤ��ұ����ı�ͼƬ
IMAGE img_avatar_peashooter;									// ������ͷ��ͼƬ
IMAGE img_avatar_sunflower;										// ���տ�ͷ��ͼƬ

//��תͼ��
static void flip_altas(Atlas& src, Atlas& dst)
{
	dst.clear();
	for (int i = 0; i < src.get_size(); i++)
	{
		IMAGE img_flipped;
		flip_image(src.get_image(i), &img_flipped);
		dst.add_image(img_flipped);
	}
}

//������Դ
static void load_game_resource()
{
	AddFontResourceEx(_T("resources/IPix.tff"), FR_PRIVATE, NULL);
	
	// 1. ���˵�����
	loadimage(&img_menu_background, _T("resources/menu_background.png"));
	// 2. ѡ�ǽ������ԴͼƬ
	loadimage(&img_VS, _T("resources/VS.png"));
	loadimage(&img_1P, _T("resources/1P.png"));
	loadimage(&img_2P, _T("resources/2P.png"));
	loadimage(&img_1P_desc, _T("resources/1P_desc.png"));
	loadimage(&img_2P_desc, _T("resources/2P_desc.png"));
	loadimage(&img_gravestone_right, _T("resources/gravestone.png"));
	flip_image(&img_gravestone_right, &img_gravestone_left);
	loadimage(&img_selector_tip, _T("resources/selector_tip.png"));
	loadimage(&img_selector_background, _T("resources/selector_background.png"));
	loadimage(&img_1P_selector_btn_idle_right, _T("resources/1P_selector_btn_idle.png"));
	flip_image(&img_1P_selector_btn_idle_right, &img_1P_selector_btn_idle_left);
	loadimage(&img_1P_selector_btn_down_right, _T("resources/1P_selector_btn_down_left.png"));
	flip_image(&img_1P_selector_btn_down_right, &img_1P_selector_btn_down_left);
	loadimage(&img_2P_selector_btn_idle_right, _T("resources/2P_selector_btn_idle_left.png"));
	flip_image(&img_2P_selector_btn_idle_right, &img_2P_selector_btn_idle_left);
	loadimage(&img_2P_selector_btn_down_right, _T("resources/2P_selector_btn_down_left.png"));
	flip_image(&img_2P_selector_btn_idle_right, &img_2P_selector_btn_idle_left);
	loadimage(&img_peashooter_selector_background_right, _T("resources/peashooter_selector_background_left.png"));
	flip_image(&img_peashooter_selector_background_right, &img_peashooter_selector_background_left);
	loadimage(&img_sunflower_selector_background_right, _T("resources/sunflower_selector_background_left.png"));
	flip_image(&img_sunflower_selector_background_right, &img_sunflower_selector_background_left);
	// 3. ��Ϸ�������ԴͼƬ
	loadimage(&img_sky, _T("resources/sky.png"));
	loadimage(&img_hills, _T("resources/hills.png"));
	loadimage(&img_platform_large, _T("resources/platform_large.png"));
	loadimage(&img_platform_small, _T("resources/platform_small.png"));
	loadimage(&img_1P_cursor, _T("resources/1P_cursor.png"));
	loadimage(&img_2P_cursor, _T("resources/2P_cursor.png"));
	// 4.��Ϸ(ս��)�����ɫ�ĵ���Դ
	atlas_peashooter_idle_right.load_from_file(_T("resources/peashooter_idle_%d.png"), 9);
	flip_altas(atlas_peashooter_idle_right, atlas_peashooter_idle_left);
	atlas_peashooter_run_right.load_from_file(_T("resources/peashooter_run_%d.png"), 5);
	flip_altas(atlas_peashooter_run_right, atlas_peashooter_run_left);
	atlas_peashooter_attack_ex_right.load_from_file(_T("resources/peashooter_attack_ex_%d.png"), 3);
	flip_altas(atlas_peashooter_attack_ex_right, atlas_peashooter_attack_ex_left);
	atlas_peashooter_die_right.load_from_file(_T("resources/peashooter_die_%d.png"), 4);
	flip_altas(atlas_peashooter_die_right, atlas_peashooter_die_left);
	atlas_sunflower_idle_right.load_from_file(_T("resources/sunflower_idle_%d.png"), 8);
	flip_altas(atlas_sunflower_idle_right, atlas_sunflower_idle_left);
	atlas_sunflower_run_right.load_from_file(_T("resources/sunflower_run_%d.png"), 5);
	flip_altas(atlas_sunflower_run_right, atlas_sunflower_run_left);
	atlas_sunflower_attack_ex_right.load_from_file(_T("resources/sunflower_attack_ex_%d.png"), 9);
	flip_altas(atlas_sunflower_attack_ex_right, atlas_sunflower_attack_ex_left);
	atlas_sunflower_die_right.load_from_file(_T("resources/sunflower_die_%d.png"), 2);
	flip_altas(atlas_sunflower_die_right, atlas_sunflower_die_left);
	// 5.��Ϸ(ս��)������������Դ
	loadimage(&img_pea, _T("resources/pea.png"));
	atlas_pea_break.load_from_file(_T("resources/pea_break_%d.png"), 3);
	atlas_sun.load_from_file(_T("resources/sun.png_%d"), 5);
	atlas_sun_explode.load_from_file(_T("resources/sun_explode_%d.png"), 5);
	atlas_sun_ex.load_from_file(_T("resources/sun_ex.png_%d"), 5);
	atlas_sun_ex_explode.load_from_file(_T("resources/sun_ex_explode_%d.png"), 5);
	atlas_sun_text.load_from_file(_T("resources/sun_text_%d.png"), 6);
	atlas_run_effect.load_from_file(_T("resources/run_effect_%d.png"), 4);
	atlas_jump_effect.load_from_file(_T("resources/jump_effect_%d.png"), 5);
	atlas_land_effect.load_from_file(_T("resources/land_effect_%d.png"), 2);
	// 6. ��Ϸ�����������Դ
	loadimage(&img_1P_winner, _T("resources/1P_winner.png"));
	loadimage(&img_2P_winner, _T("resources/2P_winner.png"));
	loadimage(&img_winner_bar, _T("resources/winner_bar.png"));
	loadimage(&img_avatar_peashooter, _T("resources/avatar_peashooter.png"));
	loadimage(&img_avatar_sunflower, _T("resources/avatar_sunflower.png"));

	mciSendString(_T("open resours/bgm_game.mp3 alias bgm_mp3"), NULL, 0, NULL);
	mciSendString(_T("open resours/bgm_menu.mp3 alias bgm_menu"), NULL, 0, NULL);
	mciSendString(_T("open resours/pea_break_1.mp3 alias pea_break_1"), NULL, 0, NULL);
	mciSendString(_T("open resours/pea_break_2.mp3 alias pea_break_2"), NULL, 0, NULL);
	mciSendString(_T("open resours/pea_break_3.mp3 alias pea_break_3"), NULL, 0, NULL);
	mciSendString(_T("open resours/pea_shoot_1.mp3 alias pea_shoot_1"), NULL, 0, NULL);
	mciSendString(_T("open resours/pea_shoot_2.mp3 alias pea_shoot_2"), NULL, 0, NULL);
	mciSendString(_T("open resours/pea_shoot_ex.mp3 alias pea_shoot_ex"), NULL, 0, NULL);
	mciSendString(_T("open resours/sun_explode.mp3 alias sun_explode"), NULL, 0, NULL);
	mciSendString(_T("open resours/sun_explode_ex.mp3 alias sun_explode_ex"), NULL, 0, NULL);
	mciSendString(_T("open resours/sun_text.mp3 alias sun_text"), NULL, 0, NULL);
}

int main()
{
	ExMessage msg;
	const int FPS = 60;

	initgraph(1280, 720);
	BeginBatchDraw();//��ͣ����������ڻ���

	menu_scene = new MenuScene();
	game_scene = new GameScene();
	selector_scene = new SelectorScene();

	load_game_resource();
	scene_manager.set_current_scene(menu_scene);//��ʼ��:���������� �� menu_scene
	while (true)
	{
		DWORD frame_star_time = GetTickCount();

		while (peekmessage(&msg))
		{
			scene_manager.on_input(msg);
		}

		static DWORD last_tick_time = GetTickCount();
		DWORD current_tick_time = GetTickCount();
		DWORD delta_tick_time = current_tick_time - last_tick_time;
		scene_manager.on_update(delta_tick_time);
		last_tick_time = GetTickCount();

		cleardevice();//ʹ�ñ���ɫ��մ���
		scene_manager.on_draw();
		FlushBatchDraw();//������洰��

		DWORD frame_end_time = GetTickCount();
		DWORD frame_delete_time = frame_end_time - frame_star_time;
		if (frame_delete_time < 1000 / FPS)
			Sleep(1000 / FPS - frame_delete_time);
	}
	EndBatchDraw();
	return 0;
}