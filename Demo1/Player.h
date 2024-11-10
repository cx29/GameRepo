#include"Animation.h"
#pragma once
class Player :public Animation
{
public:
	Player();
	Player(LPCTSTR leftPath, LPCTSTR rightPath, int num, int interval, FloatPOINT& initPos, float initialHealth, int window_width, int window_height);

	/// <summary>
/// 播放动画
/// </summary>
/// <param name="delta"></param>
	void PlayAnimation(int delta);

	/// <summary>
	/// 返回玩家的血量
	/// </summary>
	/// <returns></returns>
	float GetHealth() const;

	/// <summary>
	/// 玩家扣血
	/// </summary>
	/// <param name="damage"></param>
	void TakeDamage(float damage);
	/// <summary>
	/// 将玩家的坐标返回出去
	/// </summary>
	/// <returns></returns>
	FloatPOINT& GetPos();

	/// <summary>
	/// 监控键盘输入事件
	/// </summary>
	void ProcessLinstenKey(const ExMessage& msg);

private:
	/// <summary>
		/// 玩家移动
		/// </summary>
		/// <param name="direction">移动方向</param>
		/// <param name="speed">移动速度</param>
		/// <param name="fixedTimeStep">fps</param>
	void Move(const FloatPOINT& direction, float speed, float fixedTimeStep);

private:
	//玩家四个移动方向的判断
	bool is_move_up = false;
	bool is_move_down = false;
	bool is_move_right = false;
	bool is_move_left = false;
	const int WINDOW_WIDTH;
	//移动速度
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
