#include "bomber.h"

Bomber::Bomber(int x, int y, int argumentCount, char** arguments) {
    this->x = x;
    this->y = y;
    this->argumentCount = argumentCount;
    this->args = arguments;
    this->isAlive = true;
    aliveCount++;
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

void Bomber::setIsAlive(bool isAlive) {
    this->isAlive = isAlive;
    if (isAlive) {
        aliveCount++;
    } else {
        aliveCount--;
    }
}

bool Bomber::getIsAlive() {
    return this->isAlive;
}

int Bomber::aliveCount = 0;