#ifndef _ATLAS_H_
#define _ATLAS_H_

#include <graphics.h>
#include <vector>

class Atlas
{
public:
	Atlas() = default;
	~Atlas() = default;

	void load_from_file(LPCTSTR path, int num)//加载图片资源
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

#endif // !_ATLAS_H_
