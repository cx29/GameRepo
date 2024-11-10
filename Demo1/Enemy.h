#include"FloatPOINT.h"
#include"Player.h"
#include"Bullet.h"
#include"Animation.h"
#include"graphics.h"
#pragma once

class Enemy :public Animation
{
public:
	Enemy(LPCTSTR leftPath, LPCTSTR rightPath, LPCTSTR shadowPath, int num, int interval, int window_width, int window_height);

	~Enemy() {}
	/// <summary>
	/// 判断是否撞击到武器w
	/// </summary>
	/// <param name="bullet"></param>
	/// <returns></returns>
	bool CheckBulletCollision(const Bullet& bullet);
	/// <summary>
	/// 判断是否撞击到玩家
	/// </summary>
	/// <param name="player"></param>
	/// <returns></returns>
	bool CheckPlayerCollision(const Player& player);
	/// <summary>
	/// 移动方法,朝着玩家在的方向移动
	/// </summary>
	/// <param name="player"></param>
	void Move(const Player& player, int delta);

private:
	const int SPEED = 2;
	const float FIXEDTIMESTEP = 0.016f;
	const int FRAME_WIDTH = 80;
	const int FRAME_HEIGHT = 80;
	const int SHADOW_WIDTH = 48;
	const int WINDOW_WIDTH;
	const int WINDOW_HEIGHT;

	FloatPOINT pos;
};
