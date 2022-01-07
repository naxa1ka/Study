#include "MovableWall.h"
#include "GameWorld.h"
MovableWall::MovableWall(int InitX, int InitY, int Width, int Height, int Speed): Wall(InitX, InitY, Width, Height)
{
	this->Speed = Speed;
}

void MovableWall::Update()
{
	MoveTo(X-Speed, Y);

	if (X < GameWorld::GetBorder()) { 
		GameWorld::DecreaseScore();
		Entity::Destroy();
	}
}

HPEN MovableWall::SetColor()
{
	return CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
}

void MovableWall::Destroy()
{
	GameWorld::IncreaseScore();
}
