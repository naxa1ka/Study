#include "Location.h"

Location::Location(int InitX, int InitY) {
    X = InitX; 
    Y = InitY;
};

Location::~Location() {
};

int Location::GetX() {
    return X;
};


int Location::GetY() {
    return Y;
};
