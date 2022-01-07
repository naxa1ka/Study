#pragma once
#include "Direction.h"
#include "IBulletFactory.h"
class ShieldBulletFactory : public IBulletFactory //пуля которая способна пробивать несколько стенок
{
	void CreateBullet(int InitX, int InitY, DIRECTION direction) override;
};

