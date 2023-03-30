#ifndef PARSER_H
#define PARSER_H

#include "components/bomb.h"
#include "components/bomber.h"
#include "components/map.h"
#include "components/obstacle.h"
#include <iostream>

class Parser {
public:
    Parser();
    std::vector<Bomb> getBombs();
    std::vector<Bomber> getBombers();
    std::vector<Obstacle> getObstacles();
    Map getMap();
    void Print();
private:
    std::vector<Bomb> bombs;
    std::vector<Bomber> bombers;
    std::vector<Obstacle> obstacles;
    Map map;
};


#endif //PARSER_H
