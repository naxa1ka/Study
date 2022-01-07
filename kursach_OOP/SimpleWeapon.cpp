#include "SimpleWeapon.h"

void SimpleWeapon::Attack(int MuzzleX, int MuzzleY, DIRECTION direction, IBulletFactory* bullet)
{
	bullet->CreateBullet(MuzzleX, MuzzleY, direction);
}
