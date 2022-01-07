#pragma once

#include "Point.h"

class Rect : public Point { //класс прямоугольник используется для более простой закраски объектов
                            //а также является вспомогательным для работы системы столкновений
protected:
    int Width;
    int Height;
public:
    Rect(int InitX, int InitY, int InitWidth, int InitHeight);

    Rect(int InitX, int InitY);
    
    ~Rect();

    int GetWidth();

    int GetHeight();

    virtual void Show() override;

    virtual void Hide() override;
};

