#pragma once
#include "Direction.h"
#include "IBulletFactory.h"
class RedBulletFactory : public IBulletFactory //красная пуля
{
	void CreateBullet(int InitX, int InitY, DIRECTION direction) override;
};

