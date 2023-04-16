#include "obstacle.h"

Obstacle::Obstacle(int x, int y, int durability, Map& map) {
    this->x = x;
    this->y = y;
    this->durability = durability;
    map.setObstacle(x, y);
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

void Obstacle::setDurability(int durability) {
    this->durability = durability;
}

void Obstacle::Print() {
    std::cout << "Obstacle: " << x << " " << y << " " << durability << std::endl;
}