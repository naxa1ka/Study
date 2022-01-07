#include "ShieldBulletFactory.h"
#include "ShieldBullet.h"

void ShieldBulletFactory::CreateBullet(int InitX, int InitY, DIRECTION direction)
{
	new ShieldBullet(InitX, InitY, direction);
}
