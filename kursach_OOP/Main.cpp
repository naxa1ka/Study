#pragma once                  
#include <windows.h>
#include <conio.h>
#include <iostream>   
#include <thread>
#include <chrono>
using namespace std;        // Пространство имен std

#include "Tank.h" 	//объявление классов
#include "GetConlWin.h"		//указатель на консольное окно
#include "Entity.h"
#include "EntityHandler.h"
#include "Bullet.h"
#include "Wall.h"
#include "WallGenerator.h"
#include "GameWorld.h"
//макрос для определения кода нажатой клавиши
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*   Г Л О Б А Л Ь Н Ы Е   П Е Р Е М Е Н Н Ы Е  И  К О Н С Т А Н Т Ы   */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

//первичное объявление глобальной переменной
//глобальная переменная действует от места объявления до конца файла
//, в котором объявлена

HDC hdc;	// Объявим контекст устройства
			// Контекст устройства по сути это структура,
			// содержащая описание видеокарты на вашем компьютере
			// и всех необходимых графических элементов


/***********************************************************************/
/*               О С Н О В Н А Я    П Р О Г Р А М М А                  */
/***********************************************************************/
void WINAPI EntitySystem() {
	while (true)
	{
		EntityHandler::UpdateAll();
		Sleep(25);
	}	
}


void WINAPI GameLoop() {
	while (true)
	{
		GameWorld::Update();
		Sleep(500);
	}

}

void WINAPI WallGeneratorSystem() {
	while (true)
	{
		WallGenerator::Update();
		Sleep(25);
	}
}


int main()
{
	HWND hwnd = GetConcolWindow();
	system("color F0");

	if (hwnd != NULL)
	{
		//получим контекст устройства для консольного окна
		hdc = GetWindowDC(hwnd);
		//если контекст существует - можем работать
		if (hdc != 0)
		{
			

			WallGenerator::SetDelay(4500); //задержка перед созданием новой партии стенок
			WallGenerator::SetChance(3); //шанс выпадения бонусной стенки - чем выше тем хуже

			Tank tank(100, 200);  //инициализация корабля
			
			HANDLE CollThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)GameLoop, 0, 0, 0);
			HANDLE SecondThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)WallGeneratorSystem, 0, 0, 0);
			HANDLE Thread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)EntitySystem, 0, 0, 0);

			GameWorld::Start();
			while (1)	//бесконечный цикл буксировки фигуры
			{
				if (KEY_DOWN(VK_ESCAPE))     //конец работы 27
					break;

				//направление движения объекта

				if (KEY_DOWN(VK_LEFT)) //стрелка влево  37
				{
					tank.MoveTo(LEFT);
					Sleep(5);
				}

				if (KEY_DOWN(VK_RIGHT)) //стрелка вправо  39
				{
					tank.MoveTo(RIGHT);
					Sleep(5);
				}

				if (KEY_DOWN(VK_DOWN)) //стрелка вниз  40
				{
					tank.MoveTo(DOWN);
					Sleep(5);
				}

				if (KEY_DOWN(VK_UP)) //стрелка вверх  38
				{
					tank.MoveTo(UP);
					Sleep(5);
				}

				if (KEY_DOWN(VK_SPACE)) //стрелка вверх  38
				{
					tank.Shoot();
					Sleep(500);
				}
			}
		}
	}
	return 0;
}

