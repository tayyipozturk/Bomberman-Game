#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <iostream>
#include "map.h"

class Obstacle {
public:
    Obstacle(int x, int y, int durability, Map& map);
    int getX();
    int getY();
    int getDurability();
    void setDurability(int durability);
    void Print();
private:
    int x;
    int y;
    int durability;
};


#endif //OBSTACLE_H
