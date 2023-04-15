#ifndef BOMBER_H
#define BOMBER_H

#include <string>
#include <vector>
#include <iostream>

extern "C" {
    #include <unistd.h>
}
extern "C" {
    #include "../logging.h"
}

#include "map.h"
#include "obstacle.h"
#include "bomb.h"

class Bomber {
public:
    Bomber(int x, int y, int argumentCount, char** arguments);
    int getX();
    int getY();
    int getArgumentCount();
    char** getArgs();
    void setIsAlive(bool isAlive);
    bool getIsAlive();
    void Print();
    static int aliveCount;
    static int dieLog;

    void Start(int socket, Map& map, omp* omp);
    void See(int socket, Map& map, omp* omp, std::vector<Bomber>& bombers, std::vector<Obstacle>& obstacles, std::vector<Bomb>& bombs);
    std::vector<od> getVision(std::vector<Bomber>& bombers, std::vector<Obstacle>& obstacles, std::vector<Bomb>& bombs);
    void Move(int socket, Map& map, omp* omp, std::vector<Bomber>& bombers, std::vector<Obstacle>& obstacles, std::vector<Bomb>& bombs, coordinate target);
    void PlantBomb(int socket, Map& map, omp* omp, std::vector<Bomber>& bombers, std::vector<Obstacle>& obstacles, std::vector<Bomb>& bombs);
private:
    int x;
    int y;
    int argumentCount;
    char** args;
    bool isAlive;
};


#endif //BOMBER_H
