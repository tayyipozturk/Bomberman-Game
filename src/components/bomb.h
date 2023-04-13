#ifndef BOMB_H
#define BOMB_H

#include <iostream>

class Bomb {
public:
    Bomb(int x, int y, unsigned int radius, long interval);
    int getX();
    int getY();
    unsigned int getRadius();
    long getInterval();
    void setIsLive(bool isAlive);
    bool getIsLive();
    void explode();
    void Print();
    static int liveCount;
private:
    int x;
    int y;
    unsigned int radius;
    long interval;
    bool isLive;
};


#endif //BOMB_H
