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
    this->isLive = isLive;
}

bool Bomb::getIsLive() {
    return this->isLive;
}

void Bomb::Print() {
    std::cout << "Bomb at (" << this->x << ", " << this->y << ") with range " << this->radius << " and timer " << this->interval << std::endl;
}

std::vector<od>  Bomb::getVision(unsigned int radius, Map& map) {
    std::vector<od> damagedObjects;
    bool up, down, left, right;                                     // flags to check if a way is blocked by an obstacle
    up = down = left = right = true;
    if(map.getOccupancy(this->x, this->y) == BOMBER_OBJ) {          // check if the bomb is on a bomber
        damagedObjects.push_back({{this->x, this->y}, BOMBER});
    }
    else if (map.getOccupancy(this->x, this->y) == BOMBER_AND_BOMB) {
        damagedObjects.push_back({{this->x, this->y}, BOMBER});
    }
    for (int i = 1; i <= radius; i++) {
        if (right && (this->x + i < map.getWidth())) {              // check if the way is blocked by an obstacle and the index is in the map
            if (map.getOccupancy(this->x + i, this->y) == OBSTACLE_OBJ) {
                damagedObjects.push_back({{this->x + i, this->y}, OBSTACLE});
                right = false;
            }
            else if (map.getOccupancy(this->x + i, this->y) == BOMBER_OBJ || map.getOccupancy(this->x + i, this->y) == BOMBER_AND_BOMB) {
                damagedObjects.push_back({{this->x + i, this->y}, BOMBER});
            }
        }
        if (left && (this->x - i >= 0)){                            // check if the way is blocked by an obstacle and the index is in the map
            if (map.getOccupancy(this->x - i, this->y) == OBSTACLE_OBJ) {
                damagedObjects.push_back({{this->x - i, this->y}, OBSTACLE});
                left = false;
            }
            else if (map.getOccupancy(this->x - i, this->y) == BOMBER_OBJ || map.getOccupancy(this->x - i, this->y) == BOMBER_AND_BOMB) {
                damagedObjects.push_back({{this->x - i, this->y}, BOMBER});
            }
        }
        if (down && (this->y + i < map.getHeight())){               // check if the way is blocked by an obstacle and the index is in the map
            if (map.getOccupancy(this->x, this->y + i) == OBSTACLE_OBJ) {
                damagedObjects.push_back({{this->x, this->y + i}, OBSTACLE});
                down = false;
            }
            else if (map.getOccupancy(this->x, this->y + i) == BOMBER_OBJ || map.getOccupancy(this->x, this->y + i) == BOMBER_AND_BOMB) {
                damagedObjects.push_back({{this->x, this->y + i}, BOMBER});
            }
        }
        if (up && (this->y - i >= 0)){                              // check if the way is blocked by an obstacle and the index is in the map
            if (map.getOccupancy(this->x, this->y - i) == OBSTACLE_OBJ) {
                damagedObjects.push_back({{this->x, this->y - i}, OBSTACLE});
                up = false;
            }
            else if (map.getOccupancy(this->x, this->y - i) == BOMBER_OBJ || map.getOccupancy(this->x, this->y - i) == BOMBER_AND_BOMB) {
                damagedObjects.push_back({{this->x, this->y - i}, BOMBER});
            }
        }
    }
    return damagedObjects;
}
