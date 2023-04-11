#include "bomber.h"

Bomber::Bomber(int x, int y, int argumentCount, char** arguments) {
    this->x = x;
    this->y = y;
    this->argumentCount = argumentCount;
    this->args = arguments;
}

int Bomber::getX() {
    return this->x;
}

int Bomber::getY() {
    return this->y;
}

int Bomber::getArgumentCount() {
    return this->argumentCount;
}

char** Bomber::getArgs() {
    return this->args;
}