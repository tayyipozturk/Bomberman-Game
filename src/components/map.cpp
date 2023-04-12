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