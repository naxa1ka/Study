#pragma once
#include "IWeapon.h"
class QueueWeapon : public IWeapon //стрельба очередью
{
	void Attack(int MuzzleX, int MuzzleY, DIRECTION direction, IBulletFactory* bullet) override;
};

