#include "GameWorld.h"
#include <Windows.h>
#include <cmath>
extern HDC hdc;
LOGFONT font;

void GameWorld::IncreaseScore()
{
	Score++;
	UpdateScore();
}

void GameWorld::DecreaseScore()
{
	if (Score > 0) {
		Score--;
		UpdateScore();
	}
}

void GameWorld::Update()
{
	
	RECT r;
	r.left = 0+Border;
	r.top = 0;
	r.right = SizeX;
	r.bottom = SizeY;
	HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));
	FillRect(hdc, &r, brush);
	DeleteObject(brush);

	HPEN pen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	SelectObject(hdc, pen);
	MoveToEx(hdc, Border, 0, NULL);
	LineTo(hdc, Border, SizeY);
	DeleteObject(pen);

	
}

void GameWorld::UpdateScore()
{
	char result[16];
	_itoa_s(Score, result, 10);
	TextOutA(hdc, Border - 75, 50, (LPCSTR)result, log10(Score)+1);
}

void GameWorld::Start()
{
	font.lfHeight = 50;
	HFONT hfont;
	hfont = ::CreateFontIndirect(&font);
	SelectObject(hdc, hfont);
}

int GameWorld::GetSizeX()
{
	return SizeX;
}

int GameWorld::GetSizeY()
{
	return SizeY;
}

int GameWorld::GetBorder()
{
	return Border;
}


int GameWorld::Score = 0;

int GameWorld::SizeX = 1600;

int GameWorld::SizeY = 800;

int GameWorld::Border = 200;