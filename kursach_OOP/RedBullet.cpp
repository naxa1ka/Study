#include "RedBullet.h"

RedBullet::RedBullet(int InitX, int InitY, DIRECTION direction) : Bullet(InitX, InitY, direction)
{
}

RedBullet::~RedBullet()
{
}

HPEN RedBullet::SetColor()
{
	return CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
}
