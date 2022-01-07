#pragma once
#include "Direction.h"
#include "IBulletFactory.h"
class MagicBulletFactory : public IBulletFactory //магическая пуля
{
	void CreateBullet(int InitX, int InitY, DIRECTION direction) override;
};


