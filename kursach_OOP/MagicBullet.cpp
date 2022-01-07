#include "MagicBullet.h"
MagicBullet::MagicBullet(int InitX, int InitY, DIRECTION direction) : Bullet(InitX, InitY, direction)
{
}

MagicBullet::~MagicBullet()
{
}

void MagicBullet::Update()
{
	switch (direction)
	{
	case UP:
		MoveTo(X-5, Y - 5);
		MoveTo(X+5, Y - 5);
		break;
	case DOWN:
		MoveTo(X-5, Y + 5);
		MoveTo(X+5, Y + 5);
		break;
	case LEFT:
		MoveTo(X - 5, Y+5);
		MoveTo(X - 5, Y-5);
		break;
	case RIGHT:
		MoveTo(X + 5, Y+5);
		MoveTo(X + 5, Y-5);
		break;
	}
}


HPEN MagicBullet::SetColor()
{
	return CreatePen(PS_SOLID, 2, RGB(255, 0, 255));
}