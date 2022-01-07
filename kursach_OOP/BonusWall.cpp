#include "BonusWall.h"
#include "WeaponBonus.h"
#include "BulletBonus.h"
#include "GameWorld.h"
#include <iostream>
BonusWall::BonusWall(int InitX, int InitY, int Width, int Height, int Speed) : MovableWall(InitX, InitY, Width, Height, Speed)
{
}

void BonusWall::Destroy()
{
	if (rand() % 2) 
		new BulletBonus(X, Y);
	else
		new WeaponBonus(X, Y);
	
	GameWorld::IncreaseScore();
	GameWorld::IncreaseScore();
}

HPEN BonusWall::SetColor()
{
	return CreatePen(PS_SOLID, 3, RGB(255, 128, 255));
}
