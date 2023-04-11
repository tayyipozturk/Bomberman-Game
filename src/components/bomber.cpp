#include "bomber.h"

Bomber::Bomber(int x, int y, int argumentCount, char** arguments) {
    this->x = x;
    this->y = y;
    this->argumentCount = argumentCount;
    this->args = arguments;
//    this->isAlive = true;
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

//bool Bomber::setIsAlive(bool isAlive) {
//    this->isAlive = isAlive;
//}
//
//bool Bomber::getIsAlive() {
//    return this->isAlive;
//}