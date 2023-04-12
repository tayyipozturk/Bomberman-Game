#ifndef MAP_H
#define MAP_H

#include <iostream>

class Map {
public:
    Map();
    Map(int width, int height);
    ~Map();
    int getWidth();
    int getHeight();
    void Print();
    int getOccupancy(int x, int y);
    int getVision(int x, int y);
private:
    int width;
    int height;
    int** map;
};

typedef enum occupancy_type {
    EMPTY,
    OBSTACLE_OBJ,
    BOMBER_OBJ,
    BOMB_OBJ,
    BOMBER_AND_BOMB,
} occupancy_type;


#endif //MAP_H
