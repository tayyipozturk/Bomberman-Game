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
private:
    int width;
    int height;
    int** map;
};


#endif //MAP_H
