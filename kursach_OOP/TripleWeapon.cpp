#include "TripleWeapon.h"
void TripleWeapon::Attack(int MuzzleX, int MuzzleY, DIRECTION direction, IBulletFactory *bullet)
{
	switch (direction)
	{
	case DOWN:
	case UP:
		bullet->CreateBullet(MuzzleX - 15, MuzzleY+20, direction);
		bullet->CreateBullet(MuzzleX, MuzzleY+10, direction);
		bullet->CreateBullet(MuzzleX + 15, MuzzleY, direction);
		break;
	case LEFT:
	case RIGHT:
		bullet->CreateBullet(MuzzleX+20, MuzzleY - 15, direction);
		bullet->CreateBullet(MuzzleX+10, MuzzleY, direction);
		bullet->CreateBullet(MuzzleX, MuzzleY + 15, direction);
		break;
	}

}