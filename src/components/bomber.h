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
    void Print();
private:
    int x;
    int y;
    int argumentCount;
    char** args;
};


#endif //BOMBER_H
