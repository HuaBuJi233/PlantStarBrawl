# 植物明星大乱斗
---
## 导言  
项目教程，来自B站UP主 **Voidmatrix**， [【从零开始的C++游戏开发】船新版本的植物VS植物大乱斗 | EasyX制作植物明星大乱斗](https://www.bilibili.com/video/BV1jx4y1t7eP)，该文档用于记录项目的更新进度和遇到的问题
## 更新日志
### 2024.9.19
1. **帧数限制** 的具体实现如下：
	```C++	
	const int FPS = 60;
	
	while(true)
	{
		DWORD frame_star_time = GetTickCount();	//返回系统运行至现在的毫秒数
		......
		DWORD frame_end_time = GetTickCount();	//返回系统运行至现在的毫秒数
		DWORD frame_delete_time = frame_end_time - frame_star_time;	//计算程序中间的运行时间
		if(frame_delete_time < 1000 / FPS)	//如果程序运行时间小于60帧每帧需要的时间
			Sleep(1000 / FPS - frame_delete_time);	//程序休眠时间=60帧每帧时间-中间运行时间
	}
	```
2. 声明 **Scene类** (场景类), 添加`on_enter()` `on_input()` `on_update()` `on_draw()` `on_exit()`五个虚方法：
	```c++
	class Scene
	{
	public:
		Scene() = default;
		~Scene() = default;
	
		virtual void on_enter() {}	//进入界面
		virtual void on_input(const ExMessage& msg) {}	//读取输入
		virtual void on_update() {}	//更新界面
		virtual void on_draw() {}	//绘制界面
		virtual void on_exit() {}	//退出界面
	private:
	};
	```
3. 实现基础 **MenuScene类** (菜单界面)，**GameScene类** (游戏画面)，**SelectScene类** (选择界面)，继承自 **Scene类**。
4. 实现基础 **SceneManager类** (界面管理器)，管理子界面类：
	```C++
	//声明外部变量
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
	```
5. 实现基础 **Altas类** ，加载图片资源：
	```C++
	class Atlas
	{
    public:
        Atlas() = default;
        ~Atlas() = default;
	
        void load_from_file(LPCTSTR path, int num)//加载图片资源到vector容器
        {
            img_list.clear();//设置vector容器大小为0（不改变容器容量）
            img_list.resize(num);//设置vector容器大小
            TCHAR file_path[256];
            for (int i = 0; i < num; i++)
            {
                _stprintf_s(file_path, path, i+1);
                loadimage(&img_list[i], file_path);
            }
        }
        void clear()//清除资源容器大小
        {
            img_list.clear();
        }
        int get_size()//返回资源容器大小
        {
            return (int)img_list.size();
        }
        IMAGE* get_image(int idx)//返回资源容器中指定下标的图片资源
        {
            if (idx < 0 || idx >= img_list.size())
                return nullptr;
            return &img_list[idx];
        }
        void add_image(const IMAGE& img)//向资源容器中添加新的图片资源
        {
            img_list.push_back(img);
        }
    private:
        std::vector<IMAGE> img_list;
    };
	```

#### 总结： 搭建了基本框架结构，将游戏画面用不同的场景类实现，在每个场景类中有自己的逻辑和方法；采用“享元模式”加载图片资源，将不同资源类型加载到少数几个资源对象中，后续的对象只需使用指针调用资源对象，大大节省空间和时间。
### 2024.9.23
1. 实现基础 **Animation类** （播放器），对 **Altas** 图集进行播放，加入新概念 **“回调函数”** ，用于对动画轮播结束后，判断是否需要执行指定的回调函数操作。详情实现如下：
```C++
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
	void set_atlas(Atlas* ats) //设置Altas图集对象
	{
		on_reset();
		atlas = ats;
	}
	void set_loop(bool flag) //设置轮播状态	 
	{
		is_loop = flag;
	}
	void set_interval(int ms) //设置每次画面切换时间
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
			//如果 动画播放结束&&动画不再循环&&存在回调函数 ，则调用回调函数
			if (check_finished() && !is_loop && callback)
				callback();
		}
	}
	void on_draw(int x, int y) const
	{
		putimage_alpha(x, y, atlas->get_image(index));
	}
	int get_index_frame() //返回当前Altas图集的下标
	{
		return index;
	}
	IMAGE* get_frame(int idx) //返回指定idx下标的IMAGE资源
	{
		return atlas->get_image(idx);
	}
	bool check_finished() //检查是否播放完成
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
```
2. 创建`util.h`文件，用于存放辅助工具，本次更新在该文件中添加了 **IMAGE** 图片资源的翻转函数 `flip_image()`，其中 **IMAGE类** 中包含了 **DWORD指针** ，指向图片的每一个像素地址；还添加了“加载透明像素图片”的`putimage_alpha()`函数，具体内容如下：
```C++
#include <graphics.h>
#pragma comment(lib,"MSIMG32.LIB")

inline void flip_image(IMAGE* src, IMAGE* dst)
{
	int w = src->getwidth();
	int h = src->getheight();
	Resize(dst, w, h);
	DWORD* src_buffer = GetImageBuffer(src);
	DWORD* dst_buffer = GetImageBuffer(dst);
	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++)
		{
			int idx_src = y * w + x;
			int idx_dst = y * w + w - x - 1;
			dst_buffer[idx_dst] = src_buffer[idx_src];
		}
}

inline void putimage_alpha(int x, int y, IMAGE* img)
{
	int w = img->getwidth();
	int h = img->getheight();
	AlphaBlend(GetImageHDC(NULL), x, y, w, h,
		GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA
		});
}
```
3. 在`main.cpp`中，对外部资源声明对应 **IMAGE** 或 **Altas** 对象，根据`util.h`文件中的 **IMAGE** 图片翻转函数，创建 **Altas** 图集的翻转函数`flip_altas()`，并声明定义加载函数`load_game_resource()`对所有字体、图片、音频资源进行全部加载，其中资源声明和加载过于重复繁多，下面仅贴出部分代码：
```C++
IMAGE img_sky;													// 天空图片
IMAGE img_hills;												// 山脉图片Atlas atlas_peashooter_idle_left;								// 婉逗射手朝向左的默认动画图集
Atlas atlas_peashooter_idle_right;								// 婉逗射手朝向右的默认动画图集
Atlas atlas_peashooter_run_left;								// 婉逗射手朝向左的跑步动画图集
Atlas atlas_peashooter_run_right;								// 婉逗射手朝向右的跑步动画图集
Atlas atlas_peashooter_attack_ex_left;							// 婉逗射手朝向左的攻击动画图集
Atlas atlas_peashooter_attack_ex_right;							// 婉逗射手朝向右的攻击动画图集
MAGE img_1P_winner;											// 1P 获胜文本图片
IMAGE img_2P_winner;											// 2P 获胜文本图片
IMAGE img_winner_bar;											// 获胜玩家背景文本图片
IMAGE img_avatar_peashooter;									// 婉逗射手头像图片
IMAGE img_avatar_sunflower;										// 龙日葵头像图片
//翻转图集
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

//加载资源
static void load_game_resource()
{
	// 加载字体资源
	AddFontResourceEx(_T("resources/IPix.tff"), FR_PRIVATE, NULL);
	// 游戏界面的资源图片
	loadimage(&img_sky, _T("resources/sky.png"));
	loadimage(&img_hills, _T("resources/hills.png"));
	loadimage(&img_platform_large, _T("resources/platform_large.png"));
	loadimage(&img_platform_small, _T("resources/platform_small.png"));
	loadimage(&img_1P_cursor, _T("resources/1P_cursor.png"));
	loadimage(&img_2P_cursor, _T("resources/2P_cursor.png"));
	atlas_peashooter_idle_right.load_from_file(_T("resources/peashooter_idle_%d.png"), 9);
	flip_altas(atlas_peashooter_idle_right, atlas_peashooter_idle_left);
	atlas_peashooter_run_right.load_from_file(_T("resources/peashooter_run_%d.png"), 5);
	flip_altas(atlas_peashooter_run_right, atlas_peashooter_run_left);
	atlas_peashooter_attack_ex_right.load_from_file(_T("resources/peashooter_attack_ex_%d.png"), 3);
	flip_altas(atlas_peashooter_attack_ex_right, atlas_peashooter_attack_ex_left);
	atlas_peashooter_die_right.load_from_file(_T("resources/peashooter_die_%d.png"), 4);
	flip_altas(atlas_peashooter_die_right, atlas_peashooter_die_left);

	// 游戏结束界面的资源
	loadimage(&img_1P_winner, _T("resources/1P_winner.png"));
	loadimage(&img_2P_winner, _T("resources/2P_winner.png"));
	loadimage(&img_winner_bar, _T("resources/winner_bar.png"));
	loadimage(&img_avatar_peashooter, _T("resources/avatar_peashooter.png"));
	loadimage(&img_avatar_sunflower, _T("resources/avatar_sunflower.png"));

	//  mci控件加载音乐
	mciSendString(_T("open resours/bgm_game.mp3 alias bgm_mp3"), NULL, 0, NULL);
	......
	......
}
```
4. 实现 **Vector2类** ，用于简单的坐标存储，为实现 **Camera类** 提供前置， **Camera类** 提供了动态画面效果，提出 **“世界坐标”** 和 **“摄像机坐标”**，**“世界坐标”** 用于游戏逻辑检测，**“摄像机坐标”** ，用于画面显示，具体实现如下：
```C++
//vector2.h
	class Vector2
{
public:
	Vector2() = default;
	~Vector2() = default;
	Vector2(float x, float y)
		:x(x), y(y) {}

	float lenth() //返回向量长度
	{
		return sqrt(x * x + y * y);
	}
	Vector2 normalize() //返回单位向量
	{
		if (x == 0 && y == 0) return Vector2(0, 0);
		float len = lenth();
		return Vector2(x / len, y / len);
	}
public:
	Vector2 operator+(const Vector2& vec) const
	{
		return Vector2(x + vec.x, y + vec.y);
	}
	Vector2 operator-(const Vector2& vec) const
	{
		return Vector2(x - vec.x, y - vec.y);
	}
	void operator+=(const Vector2& vec)
	{
		x += vec.x;
		y += vec.y;
	}
	void operator-=(const Vector2& vec)
	{
		x -= vec.x;
		y -= vec.y;
	}
	float operator*(const Vector2& vec) const
	{
		return x * vec.x + y * vec.y;
	}
	Vector2 operator*(float val) const
	{
		return Vector2(x * val, y * val);
	}
	void operator*=(float val)
	{
		x *= val;
		y *= val;
	}
public:
	float x;
	float y;
};
```
```C++
//camera.h
#include "vector2.h"
class Camera
{
private:
	Vector2 position;
public:
	Camera() = default;
	~Camera() = default;

	void reset()
	{
		position.x = 0;
		position.y = 0;
	}
	void init_camera(float x, float y) //初始化相机位置
	{
		position = Vector2(x, y);
	}
	const Vector2& get_position() const
	{
		return position;
	}
	void on_update(int delay)
	{
	//根据对象具体编写，暂空。
	}
};
```
5. 更改各个场景类的 `on_update()` 函数为`on_update(int delay)` ，为动画播放器**Animation类**的同名 `on_update(int delay)` 提供延迟参数；更新各个场景类的 `on_draw()` 函数，传递的实际绘制角色位置为：世界坐标-摄像机坐标。
#### 总结：项目更新到这，各个类之间的关系也有了初步建立，IMAGE图片→Alta图片集→Animation动画播放器→Scene的各个场景→SceneManager场景管理器，其中需要注意对每个过程所用到的对象，对其private成员进行初始化；提出了 世界坐标系 和 相机坐标系 的概念，往后可以利用这个概念制作大地图和画面特效；在Animation类中使用回调函数 callback ，可以用于角色死亡后，死亡动画播放结束，才会正确执行其对象的内存清理。####