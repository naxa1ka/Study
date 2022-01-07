#pragma once
#include "MovableWall.h"
class BonusWall : public MovableWall //стена с бонусом
{
public:
	BonusWall(int InitX, int InitY, int Width, int Height, int Speed);
	virtual HPEN SetColor() override;
	void Destroy() override;
};

