#ifndef BOMBER_H
#define BOMBER_H

#include <string>
#include <vector>
#include <iostream>

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
private:
    int x;
    int y;
    int argumentCount;
    char** args;
    bool isAlive;
};


#endif //BOMBER_H
