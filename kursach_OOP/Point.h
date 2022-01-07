#pragma once

#include "Location.h"

class Point : public Location { //класс представляющий из себя точку на экране
protected:
    bool Visible; //свойство видимости на экране
public:
    Point(int InitX, int InitY); //конструктор точки

    ~Point(); //деструктор

    bool IsVisible(); //геттер для поля видимости  

    void MoveTo(int NewX, int NewY); //передвижение точки

    virtual void Show(); //показ точки на экране

    virtual void Hide();//скрыть точку на экране
};