#pragma comment(lib,"MSIMG32.LIB")
#pragma once
#include <vector>
#include <graphics.h>
#include"FloatPOINT.h"
/// <summary>
/// 动画类
/// </summary>
class Animation
{
public:
	/// <summary>
	///	构造函数
	/// </summary>
	/// <param name="lpath">左图片路径</param>
	/// <param name="rpath">右图片路径</param>
	/// <param name="num">图片数量</param>
	/// <param name="interval">帧间隔</param>
	Animation(LPCTSTR leftPath, LPCTSTR rightPath, LPCTSTR shadowPath, int num, int interval);

	~Animation();

protected:
	/// <summary>
	/// 将阴影渲染到对象的脚下,并且渲染对象到页面中
	/// </summary>
	/// <param name="dir">方向</param>
	/// <param name="pos"当前坐标></param>
	/// <param name="delta">帧间隔</param>
	/// <param name="obj_WIDTH"></param>
	/// <param name="shadow_WIDTH"></param>
	/// <param name="obj_HEIGHT"></param>
	void Play(const FloatPOINT& dir, const FloatPOINT& pos, int delta, int obj_WIDTH, int shadow_WIDTH, int obj_HEIGHT, int d_value);

private:
	int _timer = 0;//动画计时器
	int _idx_frame = 0;//动画帧索引
	int _interval_ms = 0;
	int frameLength = 1;
	IMAGE _shadow_img;

	std::vector<IMAGE*> _left_frame_list;
	std::vector<IMAGE*> _right_frame_list;
	//当前的动画列表不允许从该变量进行修改,如果需要更改动画列表的元素应该从以上两个变量进行修改
	const std::vector<IMAGE*>* _current_frame_list = nullptr;

	/// <summary>
	/// inline关键字,建议编译器插入代码的位置
	/// </summary>
	/// <param name="point"></param>
	/// <param name="img"></param>
	inline void putimage_alpha(const FloatPOINT& point, IMAGE* img);//&传入引用,*传入地址
};
