#pragma once

class Location { //класс для координат
protected:
    int X;  //координата по горизонтале
    int Y;  //координата по вертикале
public:
    Location(int InitX, int InitY);//конструктор

    ~Location(); //деструктор

    int GetX(); //геттер для икса

    int GetY(); //геттер для игрека
};
