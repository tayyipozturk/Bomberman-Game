#include "map.h"

Map::Map() {
    width = 0;
    height = 0;
}

Map::Map(int width, int height) {
    this->width = width;
    this->height = height;
    this->map = (int**) malloc(sizeof(int*) * height);
    for (int i = 0; i < height; i++) {
        this->map[i] = (int*) malloc(sizeof(int) * width);
    }
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

void Map::Print() {
    std::cout << "Map: " << width << "x" << height << std::endl;
}

int Map::getOccupancy(int x, int y) {
    return map[y][x];
}

int Map::getVision(int x, int y) {
    int count = 0;
    // left
    for (int i = 1; i < 4; i++) {
        if (x - i < 0) {
            break;
        }
        if (map[y][x - i] == OBSTACLE_OBJ) {
            count++;
            break;
        }
        else if (map[y][x - i] == BOMBER_OBJ || map[y][x - i] == BOMB_OBJ){
            count++;
        }
        else if (map[y][x - i] == BOMBER_AND_BOMB) {
            count += 2;
        }
    }
    // right
    for (int i = 1; i < 4; i++) {
        if (x + i >= width) {
            break;
        }
        if (map[y][x + i] == OBSTACLE_OBJ) {
            count++;
            break;
        }
        else if (map[y][x + i] == BOMBER_OBJ || map[y][x + i] == BOMB_OBJ){
            count++;
        }
        else if (map[y][x + i] == BOMBER_AND_BOMB) {
            count += 2;
        }
    }
    // up
    for (int i = 1; i < 4; i++) {
        if (y - i < 0) {
            break;
        }
        if (map[y - i][x] == OBSTACLE_OBJ) {
            count++;
            break;
        }
        else if (map[y - i][x] == BOMBER_OBJ || map[y - i][x] == BOMB_OBJ){
            count++;
        }
        else if (map[y - i][x] == BOMBER_AND_BOMB) {
            count += 2;
        }
    }
    // down
    for (int i = 1; i < 4; i++) {
        if (y + i >= height) {
            break;
        }
        if (map[y + i][x] == OBSTACLE_OBJ) {
            count++;
            break;
        }
        else if (map[y + i][x] == BOMBER_OBJ || map[y + i][x] == BOMB_OBJ){
            count++;
        }
        else if (map[y + i][x] == BOMBER_AND_BOMB) {
            count += 2;
        }
    }
    return count;
}