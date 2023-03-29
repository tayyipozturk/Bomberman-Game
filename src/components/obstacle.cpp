#include "obstacle.h"

Obstacle::Obstacle(int x, int y, int durability) {
    this->x = x;
    this->y = y;
    this->durability = durability;
}

int Obstacle::getX() {
    return x;
}

int Obstacle::getY() {
    return y;
}

int Obstacle::getDurability() {
    return durability;
}

void Obstacle::Print() {
    std::cout << "Obstacle: " << x << " " << y << " " << durability << std::endl;
}