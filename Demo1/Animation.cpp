#include"Animation.h"

Animation::Animation(LPCTSTR leftPath, LPCTSTR rightPath, int num, int interval)
{
	_interval_ms = interval;
	TCHAR left_path_file[256];
	TCHAR right_path_file[256];
	for (size_t i = 0; i < num; i++)
	{
		_stprintf_s(left_path_file, leftPath, i);
		_stprintf_s(right_path_file, rightPath, i);
		//new了一个对象,对应的需要delete
		IMAGE* leftFrame = new IMAGE();
		IMAGE* rightFrame = new IMAGE();
		loadimage(leftFrame, left_path_file);
		loadimage(rightFrame, right_path_file);
		_left_frame_list.push_back(leftFrame);
		_right_frame_list.push_back(rightFrame);
	}
	//当前动画列表默认指向左边动画,const修饰的变量不能进行修改,但是修饰指针,可以修改指针指向的地址
	//_current_frame_list = &_left_frame_list;
	loadimage(&_shadow_img, _T("img/shadow_player.png"));
}

Animation::~Animation()
{
	for (size_t i = 0; i < _left_frame_list.size(); i++)
	{
		delete _left_frame_list[i];
	}
	for (size_t i = 0; i < _right_frame_list.size(); i++)
	{
		delete _right_frame_list[i];
	}
	_left_frame_list.clear();
	_right_frame_list.clear();
	//_current_frame_list = nullptr;
}

void Animation::Play(const FloatPOINT& dir, const FloatPOINT& pos, int delta, int obj_WIDTH, int shadow_WIDTH, int obj_HEIGHT)
{
	//计算阴影水平位置
	float pos_shadow_x = pos.x + (obj_WIDTH / 2 - shadow_WIDTH / 2);
	//计算阴影垂直位置
	float pos_shadow_y = pos.y + obj_HEIGHT - 8;
	FloatPOINT shadow_pos = { pos_shadow_x,pos_shadow_y };
	putimage_alpha(shadow_pos, &_shadow_img);
	std::vector<IMAGE*> current = _left_frame_list;
	frameLength = _left_frame_list.size();
	if (dir.x > 0)
	{
		frameLength = _right_frame_list.size();
		current = _right_frame_list;
	}
	else if (dir.x < 0)
	{
		frameLength = _left_frame_list.size();
		current = _left_frame_list;
	}

	_timer += delta;
	if (_timer >= _interval_ms)//如果计时器到达帧间隔则切换动画图片到达下一帧,同时重置计时器
	{
		_idx_frame = (_idx_frame + 1) % frameLength;//取余确保不会数组越界
		_timer = 0;
	}

	//使用->at来对指针指向的vector内的元素进行访问
	putimage_alpha(pos, current[_idx_frame]);
}

inline void Animation::putimage_alpha(const FloatPOINT& point, IMAGE* img)
{//函数体内不需要在坐标参数的原地址上进行修改,所以传入引用可以了且使用const关键字,减少复制对象带来的内存消耗,但是在函数体内会将对应的图片修改透明度,所以需要传入地址
	int w = img->getwidth();
	int h = img->getheight();
	AlphaBlend(GetImageHDC(NULL), point.x, point.y, w, h, GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}