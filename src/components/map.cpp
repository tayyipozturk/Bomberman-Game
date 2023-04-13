#include "map.h"

Map::Map() {
    width = 0;
    height = 0;
}

Map::Map(int width, int height) {
    this->width = width;
    this->height = height;
    map = std::vector<std::vector<int>>(height, std::vector<int>(width));
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            this->map[i][j] = EMPTY;
        }
    }
}

Map::~Map() {
}

int Map::getWidth() {
    return width;
}

int Map::getHeight() {
    return height;
}

std::vector<std::vector<int>> Map::getMap() {
    return map;
}

void Map::Print() {
    std::cout << "Map:" << std::endl;
    std::cout << "Height: " << height << ", Width: " << width << std::endl;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            std::cout << MAP_PRINT(map, j, i);
            std::cout << "|";
        }
        std::cout << std::endl;
        for (int k=0; k < width; k++) {
            std::cout << "--";
        }
        std::cout << std::endl;
    }
}

int Map::getOccupancy(int x, int y) {
    return map[y][x];
}

void Map::setEmpty(int x, int y) {
    map[y][x] = EMPTY;
}

void Map::setObstacle(int x, int y) {
    map[y][x] = OBSTACLE_OBJ;
}

void Map::setBomber(int x, int y) {
    map[y][x] = BOMBER_OBJ;
}

void Map::setBomb(int x, int y) {
    map[y][x] = BOMB_OBJ;
}

void Map::setBomberAndBomb(int x, int y) {
    map[y][x] = BOMBER_AND_BOMB;
}

