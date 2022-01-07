#pragma once
#include "IBulletFactory.h"
class SimpleBulletFactory : public IBulletFactory //обычная пуля
{
	void CreateBullet(int InitX, int InitY, DIRECTION direction) override;
};

