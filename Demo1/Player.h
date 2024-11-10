#include"Animation.h"
#pragma once
class Player :public Animation
{
public:
	Player();
	Player(LPCTSTR leftPath, LPCTSTR rightPath, int num, int interval, FloatPOINT& initPos, float initialHealth, int window_width, int window_height);

	/// <summary>
/// ���Ŷ���
/// </summary>
/// <param name="delta"></param>
	void PlayAnimation(int delta);

	/// <summary>
	/// ������ҵ�Ѫ��
	/// </summary>
	/// <returns></returns>
	float GetHealth() const;

	/// <summary>
	/// ��ҿ�Ѫ
	/// </summary>
	/// <param name="damage"></param>
	void TakeDamage(float damage);
	/// <summary>
	/// ����ҵ����귵�س�ȥ
	/// </summary>
	/// <returns></returns>
	FloatPOINT& GetPos();

	/// <summary>
	/// ��ؼ��������¼�
	/// </summary>
	void ProcessLinstenKey(const ExMessage& msg);

private:
	/// <summary>
		/// ����ƶ�
		/// </summary>
		/// <param name="direction">�ƶ�����</param>
		/// <param name="speed">�ƶ��ٶ�</param>
		/// <param name="fixedTimeStep">fps</param>
	void Move(const FloatPOINT& direction, float speed, float fixedTimeStep);

private:
	//����ĸ��ƶ�������ж�
	bool is_move_up = false;
	bool is_move_down = false;
	bool is_move_right = false;
	bool is_move_left = false;
	const int WINDOW_WIDTH;
	//�ƶ��ٶ�
	const int PLAYER_SPEED = 10;
	const int WINDOW_HEIGHT;
	const int PLAYER_WIDTH = 80;
	const int PLAYER_HEIGHT = 80;
	const int SHADOW_WIDTH = 48;
	const float FIXED_TIME_STEP = 0.016f;
	FloatPOINT normalized = pos.normalized();
	FloatPOINT pos;

	float health;
};
