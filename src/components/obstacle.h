#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <iostream>

class Obstacle {
public:
    Obstacle(int x, int y, int durability);
    int getX();
    int getY();
    int getDurability();
    void Print();
private:
    int x;
    int y;
    int durability;
};


#endif //OBSTACLE_H
