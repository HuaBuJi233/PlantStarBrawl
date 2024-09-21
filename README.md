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
2. 声明 **Scene类** (场景类), 添加`on_enter()` `on_input()` `on_update()` `on_draw()` `on_exit()` 五个虚方法：
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