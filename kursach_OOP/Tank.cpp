#include "Tank.h"

#include "Bullet.h"

#include "SimpleWeapon.h"
#include "DoubleWeapon.h"
#include "TripleWeapon.h"
#include "QueueWeapon.h"
#include "SimpleBulletFactory.h"
#include "RedBulletFactory.h"
#include "MagicBulletFactory.h"
#include "ShieldBulletFactory.h"

#include <windows.h>
#include <iostream>
#include <algorithm>

extern HDC hdc;


Tank::Tank(int InitX, int InitY) :Entity(InitX, InitY)
{
	CurrentX = InitX;
	CurrentY = InitY;

	bulletLevels[3] = new ShieldBulletFactory;
	bulletLevels[0] = new SimpleBulletFactory;
	bulletLevels[1] = new RedBulletFactory;
	bulletLevels[2] = new MagicBulletFactory;
	
	weaponLevels[3] = new QueueWeapon;
	weaponLevels[0] = new SimpleWeapon;
	weaponLevels[1] = new DoubleWeapon;
	weaponLevels[2] = new TripleWeapon;
	

	bulletFactory = bulletLevels[currentBulletLevel];
	weapon = weaponLevels[currentWeaponLevel];

	Height = 40;
	Width = 40;
	Scale = 4;
}

void Tank::Show()
{ 
	HPEN pen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
	SelectObject(hdc, pen);

	Rectangle(hdc, X - 6 * Scale, Y - 6 * Scale, X + 6 * Scale, Y + 6 * Scale); //корпус
	Ellipse(hdc, X - 4 * Scale, Y + 4 * Scale, X + 4 * Scale, Y - 4 * Scale); //люк 
	
	if (direction == UP or direction == DOWN)
	{
		Rectangle(hdc, X - 9 * Scale, Y + 10 * Scale, X - 6 * Scale, Y - 10 * Scale); //левый корпус
		Rectangle(hdc, X + 6 * Scale, Y + 10 * Scale, X + 9 * Scale, Y - 10 * Scale); //правый корпус

		if (direction == UP)
		{
			Rectangle(hdc, X - 1 * Scale, Y - 3 * Scale, X + 1 * Scale, Y - 14 * Scale); //дуло
		}
		else {
			Rectangle(hdc, X - 1 * Scale, Y + 3 * Scale, X + 1 * Scale, Y + 14 * Scale); //дуло
		}
	}
	else if (direction == LEFT or direction == RIGHT) {
		Rectangle(hdc, X - 10 * Scale, Y - 9 * Scale, X + 10 * Scale, Y - 6 * Scale); //левый корпус
		Rectangle(hdc, X - 10 * Scale, Y + 9 * Scale, X + 10 * Scale, Y + 6 * Scale); //правый корпус

		if (direction == LEFT)
		{
			Rectangle(hdc, X - 3 * Scale, Y + 1 * Scale, X - 14 * Scale, Y - 1 * Scale); //дуло
		}
		else {
			Rectangle(hdc, X + 3 * Scale, Y + 1 * Scale, X + 14 * Scale, Y - 1 * Scale); //дуло
		}
	}
	DeleteObject(pen);


}

void Tank::Hide()
{
	HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));
	//закрашиваем область вокруг корабля
	RECT r;
	r.left = X - 11*Scale;
	r.right = X + 11 * Scale;
	r.top = Y + 12 * Scale;
	r.bottom = Y - 12 * Scale;
	FillRect(hdc, &r, brush);
	r.left = X - 3 * Scale;
	r.right = X + 3 * Scale;
	r.top = Y -5 * Scale;
	r.bottom = Y - 16 * Scale;
	FillRect(hdc, &r, brush);

	DeleteObject(brush);
}

void Tank::Shoot()
{
	
	switch (direction)
	{
	case UP:
		weapon->Attack(X, Y - 20 * Scale, UP, bulletFactory);
		break;
	case DOWN:
		weapon->Attack(X, Y + 20 * Scale, DOWN, bulletFactory);
		break;
	case LEFT:
		weapon->Attack(X - 20 * Scale, Y, LEFT, bulletFactory);
		break;
	case RIGHT:
		weapon->Attack(X + 20 * Scale, Y, RIGHT, bulletFactory);
		break;
	}
	
}

void Tank::SetDirection(DIRECTION direction)
{
	this->direction = direction;
}

void Tank::MoveTo(DIRECTION direction)
{	
	switch (direction)
	{
	case UP:
		CurrentY -= Step;
		break;
	case DOWN:
		CurrentY += Step;
		break;
	case LEFT:
		CurrentX -= Step;
		break;
	case RIGHT:
		CurrentX += Step;
		break;
	}
	Point::MoveTo(CurrentX, CurrentY);
	this->direction = direction;
}

void Tank::SetWeapon(IWeapon* weapon)
{
	this->weapon = weapon;
}

void Tank::SetBulletFactory(IBulletFactory* bulletFactory)
{
	this->bulletFactory = bulletFactory;
}

void Tank::Update()
{
	Show();
}

void Tank::OnCollision(Entity* entity)
{	
	if (!strcmp(typeid(*entity).name(), "class BulletBonus")) {
		IncreaseBullet();
	}

	if (!strcmp(typeid(*entity).name(), "class WeaponBonus")) {
		IncreaseWeapon();
	}
}

void Tank::IncreaseWeapon()
{
	currentWeaponLevel = Clamp(++currentWeaponLevel, 0, 3);
	SetWeapon(weaponLevels[currentWeaponLevel]);
}

void Tank::IncreaseBullet()
{
	currentBulletLevel = Clamp(++currentBulletLevel, 0, 2);
	SetBulletFactory(bulletLevels[currentBulletLevel]);
}

int Tank::Clamp(int value, int min, int max)
{
	if (value >= max)
		return max;
	else if (value <= min)
		return min;
	else
		return value;
}