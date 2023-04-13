#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <vector>
extern "C" {
    #include "../message.h"
}

class Map {
public:
    Map();
    Map(int width, int height);
    ~Map();
    int getWidth();
    int getHeight();
    std::vector<std::vector<int>> getMap();
    void Print();
    int getOccupancy(int x, int y);

    void setEmpty(int x, int y);
    void setObstacle(int x, int y);
    void setBomber(int x, int y);
    void setBomb(int x, int y);
    void setBomberAndBomb(int x, int y);
private:
    int width;
    int height;
    std::vector<std::vector<int>> map;
};

typedef enum occupancy_type {
    EMPTY,
    OBSTACLE_OBJ,
    BOMBER_OBJ,
    BOMB_OBJ,
    BOMBER_AND_BOMB,
} occupancy_type;

//macro to print map[y][x] as occupancy_type
#define MAP_PRINT(map, x, y) \
    (map[y][x] == EMPTY ? " " : \
    (map[y][x] == OBSTACLE_OBJ ? "O" : \
    (map[y][x] == BOMBER_OBJ ? "B" : \
    (map[y][x] == BOMB_OBJ ? "X" : \
    (map[y][x] == BOMBER_AND_BOMB ? "D" : \
    "E")))))

#endif //MAP_H
