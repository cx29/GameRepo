#include"Enemy.h"
#include<mutex>

Enemy::Enemy(LPCTSTR leftPath, LPCTSTR rightPath, LPCTSTR shadowPath, int num, int interval, int window_width, int window_height)
	:Animation(leftPath, rightPath, shadowPath, num, interval), WINDOW_WIDTH(window_width), WINDOW_HEIGHT(window_height)
{
	enum class SpawnEdge
	{
		Up = 0,
		Down,
		Left,
		Right
	};

	SpawnEdge edge = (SpawnEdge)(rand() % 4);
	switch (edge)
	{
	case SpawnEdge::Up:
		pos.x = rand() % WINDOW_WIDTH;
		pos.y = -FRAME_HEIGHT;
		break;
	case SpawnEdge::Down:
		pos.x = rand() % WINDOW_WIDTH;
		pos.y = WINDOW_HEIGHT;
		break;
	case SpawnEdge::Left:
		pos.x = -FRAME_WIDTH;
		pos.y = rand() % WINDOW_HEIGHT;
		break;
	case SpawnEdge::Right:
		pos.x = WINDOW_WIDTH;
		pos.y = rand() % WINDOW_HEIGHT;
		break;
	}
}

void Enemy::Move(const Player& player, int delta)
{
	//获取到玩家当前的坐标
	const FloatPOINT& playerPos = player.GetPos();
	//得到当前敌人该往哪个方向走
	FloatPOINT normalized = (playerPos - pos).normalized();

	pos += normalized * (SPEED * FIXEDTIMESTEP);

	Play(normalized, pos, delta, FRAME_WIDTH, SHADOW_WIDTH, FRAME_HEIGHT, 24);
}