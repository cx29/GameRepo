#include"Player.h"

Player::Player(LPCTSTR leftPath, LPCTSTR rightPath, LPCTSTR shadowPath, int num, int interval, FloatPOINT& initPos, float initialHealth, int window_width, int window_height)
	:Animation(leftPath, rightPath, shadowPath, num, interval), health(initialHealth), pos(initPos), WINDOW_WIDTH(window_width), WINDOW_HEIGHT(window_height)
{
}

void Player::PlayAnimation(int delta)
{
	//计算方向
	int dir_x = is_move_right - is_move_left;
	int dir_y = is_move_down - is_move_up;
	FloatPOINT direction(dir_x, dir_y);

	if (direction.magnitude() != 0)//结构体中已经封装了对应的求模和求单位向量的函数可以直接调用
	{
		Move(direction, PLAYER_SPEED, FIXED_TIME_STEP);
	}
	Play(normalized, pos, delta, PLAYER_WIDTH, SHADOW_WIDTH, PLAYER_HEIGHT, 8);//x<=0的话则是向左
}

float Player::GetHealth() const
{
	return health;
}

FloatPOINT Player::GetPos() const
{
	return pos;
}

void Player::ProcessLinstenKey(const ExMessage& msg)
{
	if (msg.message == WM_KEYDOWN)//当按键按下
	{
		switch (msg.vkcode)
		{
		case VK_UP:
			is_move_up = true;
			break;
		case VK_DOWN:
			is_move_down = true;
			break;
		case VK_LEFT:
			is_move_left = true;
			break;
		case VK_RIGHT:
			is_move_right = true;
			break;
		}
	}
	if (msg.message == WM_KEYUP)//当按键抬起
	{
		switch (msg.vkcode)
		{
		case VK_UP:
			is_move_up = false;
			break;
		case VK_DOWN:
			is_move_down = false;
			break;
		case VK_LEFT:
			is_move_left = false;
			break;
		case VK_RIGHT:
			is_move_right = false;
			break;
		}
	}
}

void Player::Move(const FloatPOINT& direction, float speed, float fixedTimeStep)
{
	normalized = direction.normalized();

	pos += normalized * (speed * fixedTimeStep);

	if (pos.x < 0)
		pos.x = 0;
	else if (pos.x >= WINDOW_WIDTH - PLAYER_WIDTH)
		pos.x = WINDOW_WIDTH - PLAYER_WIDTH;
	if (pos.y < 0)
		pos.y = 0;
	else if (pos.y >= WINDOW_HEIGHT - PLAYER_HEIGHT)
		pos.y = WINDOW_HEIGHT - PLAYER_HEIGHT;
}