#include "WallGenerator.h"
#include "MovableWall.h"
#include "BonusWall.h"
#include "GameWorld.h"
#include <Windows.h>
#include <iostream>

void WallGenerator::Update()
{
	if (rand() % Chance) {
		new MovableWall(LastX, LastY, SizeWallsX, SizeWallsY, SpeedWalls);
	}
	else {
		new BonusWall(LastX, LastY, SizeWallsX, SizeWallsY, SpeedWalls);
	}
	Sleep(10);
	LastY += SizeWallsY * 2.5;
	if (GameWorldY < LastY)
	{
		LastY = 100;
		Sleep(Delay);
	}
	
}
void WallGenerator::SetDelay(int Delay) {
	WallGenerator::Delay = Delay;
}

void WallGenerator::SetChance(int Chance) {
	WallGenerator::Chance = Chance;
}

int WallGenerator::Chance = 15;
int WallGenerator::Delay = 4500;
int WallGenerator::GameWorldX = GameWorld::GetSizeX() - 25;
int WallGenerator::GameWorldY = GameWorld::GetSizeY() - 25;
int WallGenerator::LastX = GameWorldX - 25;
int WallGenerator::LastY = 100;
int WallGenerator::SizeWallsX = 7;
int WallGenerator::SizeWallsY = 40;
int WallGenerator::SpeedWalls = 1;