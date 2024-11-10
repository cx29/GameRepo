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
		//new��һ������,��Ӧ����Ҫdelete
		IMAGE* leftFrame = new IMAGE();
		IMAGE* rightFrame = new IMAGE();
		loadimage(leftFrame, left_path_file);
		loadimage(rightFrame, right_path_file);
		_left_frame_list.push_back(leftFrame);
		_right_frame_list.push_back(rightFrame);
	}
	//��ǰ�����б�Ĭ��ָ����߶���,const���εı������ܽ����޸�,��������ָ��,�����޸�ָ��ָ��ĵ�ַ
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
	//������Ӱˮƽλ��
	float pos_shadow_x = pos.x + (obj_WIDTH / 2 - shadow_WIDTH / 2);
	//������Ӱ��ֱλ��
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
	if (_timer >= _interval_ms)//�����ʱ������֡������л�����ͼƬ������һ֡,ͬʱ���ü�ʱ��
	{
		_idx_frame = (_idx_frame + 1) % frameLength;//ȡ��ȷ����������Խ��
		_timer = 0;
	}

	//ʹ��->at����ָ��ָ���vector�ڵ�Ԫ�ؽ��з���
	putimage_alpha(pos, current[_idx_frame]);
}

inline void Animation::putimage_alpha(const FloatPOINT& point, IMAGE* img)
{//�������ڲ���Ҫ�����������ԭ��ַ�Ͻ����޸�,���Դ������ÿ�������ʹ��const�ؼ���,���ٸ��ƶ���������ڴ�����,�����ں������ڻὫ��Ӧ��ͼƬ�޸�͸����,������Ҫ�����ַ
	int w = img->getwidth();
	int h = img->getheight();
	AlphaBlend(GetImageHDC(NULL), point.x, point.y, w, h, GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}