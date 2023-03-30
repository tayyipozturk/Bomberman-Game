#ifndef BOMBER_H
#define BOMBER_H

#include <string>
#include <vector>
#include <iostream>

class Bomber {
public:
    Bomber(int x, int y, int argumentCount, std::string executablePath, std::vector<std::string> arguments);
    int getX();
    int getY();
    int getArgumentCount();
    std::string getExecutablePath();
    std::vector<std::string> getArguments();
    void Print();
private:
    int x;
    int y;
    int argumentCount;
    std::string executablePath;
    std::vector<std::string> arguments;
};


#endif //BOMBER_H
