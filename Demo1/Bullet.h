#include"FloatPOINT.h"
#include"graphics.h"
#pragma once
class Bullet
{
public:
	FloatPOINT pos = { 0.0f,0.0f };

	Bullet() = default;
	~Bullet() = default;

	void Draw() const
	{
		setlinecolor(RGB(255, 155, 50));
		setfillcolor(RGB(200, 75, 10));
		fillcircle(pos.x, pos.y, RADIUS);
	}
private:
	const int RADIUS = 10;
};
