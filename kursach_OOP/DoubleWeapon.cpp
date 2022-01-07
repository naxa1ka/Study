#include "DoubleWeapon.h"
void DoubleWeapon::Attack(int MuzzleX, int MuzzleY, DIRECTION direction, IBulletFactory* bullet)
{
	switch (direction)
	{
	case DOWN:
	case UP:
		bullet->CreateBullet(MuzzleX-10, MuzzleY, direction);
		bullet->CreateBullet(MuzzleX+10, MuzzleY+10, direction);
		break;
	case LEFT:
	case RIGHT:
		bullet->CreateBullet(MuzzleX, MuzzleY-10, direction);
		bullet->CreateBullet(MuzzleX+10, MuzzleY+10, direction);
		break;
	}
	
}
