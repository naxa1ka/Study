#include "RedBulletFactory.h"
#include "RedBullet.h"

void RedBulletFactory::CreateBullet(int InitX, int InitY, DIRECTION direction)
{
	new RedBullet(InitX, InitY, direction);
}
