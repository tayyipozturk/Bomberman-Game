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
    //bool setIsAlive(bool isAlive);
    //bool getIsAlive();
    void Print();
private:
    int x;
    int y;
    int argumentCount;
    char** args;
    //bool isAlive;
    //static aliveCount;
};


#endif //BOMBER_H
