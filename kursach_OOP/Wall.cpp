#include "Wall.h"
#include <windows.h>
#include <iostream>
#include <regex>

extern HDC hdc;
Wall::Wall(int InitX, int InitY, int Width, int Height) : Entity(InitX, InitY, Width, Height)
{
}

Wall::~Wall()
{
}

void Wall::Update()
{
}

void Wall::OnCollision(Entity* entity)
{	
	const std::regex reg("class .*Bullet");
	if (std::regex_match(typeid(*entity).name(), reg)) {
		Entity::Destroy();
		Destroy();
	}
}

void Wall::Show()
{
	HPEN pen = SetColor();
	SelectObject(hdc, pen);
	Rectangle(hdc, X - Width, Y + Height, X + Width, Y - Height);
	DeleteObject(pen);
}


