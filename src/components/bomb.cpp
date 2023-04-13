#include "bomb.h"

int Bomb::liveCount = 0;

Bomb::Bomb(int x, int y, unsigned int radius, long interval) {
    this->x = x;
    this->y = y;
    this->radius = radius;
    this->interval = interval;
    this->isLive = true;
    liveCount++;
}

int Bomb::getX() {
    return this->x;
}

int Bomb::getY() {
    return this->y;
}

unsigned int Bomb::getRadius() {
    return this->radius;
}

long Bomb::getInterval() {
    return this->interval;
}

void Bomb::setIsLive(bool isLive) {
    if (isLive && !this->isLive) {
        liveCount++;
    } else if (!isLive && this->isLive) {
        liveCount--;
    }
}

bool Bomb::getIsLive() {
    return this->isLive;
}

void Bomb::Print() {
    std::cout << "Bomb at (" << this->x << ", " << this->y << ") with range " << this->radius << " and timer " << this->interval << std::endl;
}

void Bomb::explode() {
    //TODO: Implement
}