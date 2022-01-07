#include "Bullet.h"
#include "GameWorld.h"
#include <Windows.h>
#include <iostream>
#include <regex>
extern HDC hdc;
//#define DEBUG_COLLISION

Bullet::Bullet(int InitX, int InitY, DIRECTION direction) :Entity(InitX, InitY)
{
	Height = 7;
	Width = 7;
	this->direction = direction;
}

Bullet::~Bullet()
{
}

void Bullet::Show()
{
	HPEN pen = SetColor();
	SelectObject(hdc, pen);
	Ellipse(hdc, X - Width, Y + Height, X + Width, Y - Height);
	DeleteObject(pen);
}

void Bullet::Update()
{
	switch (direction)
	{
	case UP:
		MoveTo(X, Y - 10);
		break;
	case DOWN:
		MoveTo(X, Y + 10);
		break;
	case LEFT:
		MoveTo(X - 10, Y);
		break;
	case RIGHT:
		MoveTo(X + 10, Y);
		break;
	}

	if (X < 0 || Y < 0 || X > GameWorld::GetSizeX() || Y > GameWorld::GetSizeY()) {
		Destroy();
	}
}

void Bullet::OnCollision(Entity* entity)
{
	const std::regex reg("class .*Bonus");
	if (!std::regex_match(typeid(*entity).name(), reg)) {
		Destroy();
	}
}

HPEN Bullet::SetColor()
{
	return CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
}
