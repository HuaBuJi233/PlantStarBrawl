#ifndef _ATLAS_H_
#define _ATLAS_H_

#include <graphics.h>
#include <vector>

class Atlas
{
public:
	Atlas() = default;
	~Atlas() = default;

	void load_from_file(LPCTSTR path, int num)//����ͼƬ��Դ
	{
		img_list.clear();//����vector������СΪ0�����ı�����������
		img_list.resize(num);//����vector������С
		TCHAR file_path[256];
		for (int i = 0; i < num; i++)
		{
			_stprintf_s(file_path, path, i+1);
			loadimage(&img_list[i], file_path);
		}
	}
	void clear()//�����Դ������С
	{
		img_list.clear();
	}
	int get_size()//������Դ������С
	{
		return (int)img_list.size();
	}
	IMAGE* get_image(int idx)//������Դ������ָ���±��ͼƬ��Դ
	{
		if (idx < 0 || idx >= img_list.size())
			return nullptr;
		return &img_list[idx];
	}
	void add_image(const IMAGE& img)//����Դ����������µ�ͼƬ��Դ
	{
		img_list.push_back(img);
	}
private:
	std::vector<IMAGE> img_list;
};

#endif // !_ATLAS_H_
