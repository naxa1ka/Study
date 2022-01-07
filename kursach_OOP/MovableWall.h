#pragma once
#include "Wall.h"
class MovableWall: public Wall{
private:
	int Speed;
public:
	MovableWall(int InitX, int InitY, int Width, int Height, int Speed); //двигующаяся стена
	virtual void Update() override;
	virtual HPEN SetColor() override;
	virtual void Destroy() override;
};

