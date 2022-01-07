#pragma once
class WallGenerator
{
private:
	static int GameWorldX;
	static int GameWorldY;
	static int LastX;
	static int LastY;
	static int SpeedWalls;
	static int SizeWallsX;
	static int SizeWallsY;
	static int Delay;
	static int Chance;
public:
	static void Update();
	static void SetDelay(int Delay);
	static void SetChance(int Chance);
};

