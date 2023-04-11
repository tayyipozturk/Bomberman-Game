#include "parser.h"

Parser::Parser() {
    int mapWidth, mapHeight, obstacleCount, bomberCount;
    std::cin >> mapWidth >> mapHeight >> obstacleCount >> bomberCount;

    std::vector<Obstacle> obstacles;
    for (int i = 0; i < obstacleCount; i++) {
        int x, y, durability;
        std::cin >> x >> y >> durability;
        obstacles.push_back(Obstacle(x, y, durability));
    }

    std::vector<Bomber> bombers;
    for (int i = 0; i < bomberCount; i++) {
        int x, y, argumentCount;
        std::cin >> x >> y >> argumentCount;
        char** args = (char**) malloc(sizeof(char*) * (argumentCount+1));
        for (int j = 0; j < argumentCount; j++) {
            std::string argument;
            std::cin >> argument;
            args[j] = new char[argument.length()+1];
            strcpy(args[j], argument.c_str());
        }
        args[argumentCount+1] = NULL;
        bombers.push_back(Bomber(x, y, argumentCount, args));
    }

    this->map = Map(mapWidth, mapHeight);
    this->obstacles = obstacles;
    this->bombers = bombers;
}

std::vector<Bomb> Parser::getBombs() {
    return this->bombs;
}

std::vector<Bomber> Parser::getBombers() {
    return this->bombers;
}

std::vector<Obstacle> Parser::getObstacles() {
    return this->obstacles;
}

Map Parser::getMap() {
    return this->map;
}

void Parser::Print() {
    map.Print();
    for (auto obstacle : obstacles) {
        obstacle.Print();
    }
//    for (auto bomber : bombers) {
//        bomber.Print();
//    }
}
