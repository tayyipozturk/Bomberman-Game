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

    void Start(int socket);
    void Vision(int socket, Map map);
private:
    int x;
    int y;
    int argumentCount;
    char** args;
    bool isAlive;
};


#endif //BOMBER_H
