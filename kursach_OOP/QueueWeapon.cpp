#include "QueueWeapon.h"

void QueueWeapon::Attack(int MuzzleX, int MuzzleY, DIRECTION direction, IBulletFactory* bullet)
{
	switch (direction)
	{
	case UP:
	case DOWN:
		bullet->CreateBullet(MuzzleX, MuzzleY, direction);
		bullet->CreateBullet(MuzzleX, MuzzleY-15, direction);
		bullet->CreateBullet(MuzzleX, MuzzleY-30, direction);
		break;
	case LEFT:
	case RIGHT:
		bullet->CreateBullet(MuzzleX, MuzzleY, direction);
		bullet->CreateBullet(MuzzleX-15, MuzzleY, direction);
		bullet->CreateBullet(MuzzleX-30, MuzzleY, direction);
		break;

	}
	

}
