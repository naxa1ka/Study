#pragma once
#include "Bullet.h"
class IBulletFactory 
	//интерфейс, цель которого вынести логику создания пули в отдельный метод
	//таким образом, используя интерфейс можно будет динамически изменять какую
	//пулю мы хотим создать, т.к. вариант со свичом и передачей либо enum либо строки
	//будет нарушать принцип OCP и менее гибким 
{
public:
	virtual void CreateBullet(int InitX, int InitY, DIRECTION direction) = 0;
};

 