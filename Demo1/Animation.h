#pragma comment(lib,"MSIMG32.LIB")
#pragma once
#include <vector>
#include <graphics.h>
#include"FloatPOINT.h"
/// <summary>
/// ������
/// </summary>
class Animation
{
public:
	/// <summary>
	///	���캯��
	/// </summary>
	/// <param name="lpath">��ͼƬ·��</param>
	/// <param name="rpath">��ͼƬ·��</param>
	/// <param name="num">ͼƬ����</param>
	/// <param name="interval">֡���</param>
	Animation(LPCTSTR leftPath, LPCTSTR rightPath, LPCTSTR shadowPath, int num, int interval);

	~Animation();

protected:
	/// <summary>
	/// ����Ӱ��Ⱦ������Ľ���,������Ⱦ����ҳ����
	/// </summary>
	/// <param name="dir">����</param>
	/// <param name="pos"��ǰ����></param>
	/// <param name="delta">֡���</param>
	/// <param name="obj_WIDTH"></param>
	/// <param name="shadow_WIDTH"></param>
	/// <param name="obj_HEIGHT"></param>
	void Play(const FloatPOINT& dir, const FloatPOINT& pos, int delta, int obj_WIDTH, int shadow_WIDTH, int obj_HEIGHT, int d_value);

private:
	int _timer = 0;//������ʱ��
	int _idx_frame = 0;//����֡����
	int _interval_ms = 0;
	int frameLength = 1;
	IMAGE _shadow_img;

	std::vector<IMAGE*> _left_frame_list;
	std::vector<IMAGE*> _right_frame_list;
	//��ǰ�Ķ����б�����Ӹñ��������޸�,�����Ҫ���Ķ����б��Ԫ��Ӧ�ô������������������޸�
	const std::vector<IMAGE*>* _current_frame_list = nullptr;

	/// <summary>
	/// inline�ؼ���,�����������������λ��
	/// </summary>
	/// <param name="point"></param>
	/// <param name="img"></param>
	inline void putimage_alpha(const FloatPOINT& point, IMAGE* img);//&��������,*�����ַ
};
