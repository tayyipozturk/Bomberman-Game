#ifndef BOMB_H
#define BOMB_H

#include <iostream>
#include "map.h"

class Bomb {
public:
    Bomb(int x, int y, unsigned int radius, long interval);
    int getX();
    int getY();
    unsigned int getRadius();
    long getInterval();
    void setIsLive(bool isAlive);
    bool getIsLive();
    void Print();
    static int liveCount;
    std::vector<od> getVision(unsigned int radius, Map& map);
private:
    int x;
    int y;
    unsigned int radius;
    long interval;
    bool isLive;
};


#endif //BOMB_H
