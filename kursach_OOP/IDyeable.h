#pragma once
#include <Windows.h>
class IDyeable //интерфейс для покраски объектов
{
	virtual HPEN SetColor() = 0;
};

