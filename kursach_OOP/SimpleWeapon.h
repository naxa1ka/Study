#pragma once
#include "IWeapon.h"
class SimpleWeapon : public IWeapon //обычная стрельба
{
	void Attack(int MuzzleX, int MuzzleY, DIRECTION direction, IBulletFactory* bullet) override;
};

