#pragma once
class GameWorld
{
private:
	static int Score;
	static int SizeX;
	static int SizeY;
	static int Border;
public:
	static void IncreaseScore();
	static void DecreaseScore();
	static void Update();
	static void Start();
	static int GetSizeX();
	static int GetSizeY();
	static int GetBorder();
	static void UpdateScore();
};
