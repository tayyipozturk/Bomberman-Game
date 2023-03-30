#include "bomber.h"

Bomber::Bomber(int x, int y, int argumentCount, std::string executablePath, std::vector<std::string> arguments) {
    this->x = x;
    this->y = y;
    this->argumentCount = argumentCount;
    this->executablePath = executablePath;
    this->arguments = arguments;
}

int Bomber::getX() {
    return this->x;
}

int Bomber::getY() {
    return this->y;
}

int Bomber::getArgumentCount() {
    return this->argumentCount;
}

std::string Bomber::getExecutablePath() {
    return this->executablePath;
}

std::vector<std::string> Bomber::getArguments() {
    return this->arguments;
}

void Bomber::Print() {
    std::cout << "Bomber at (" << this->x << ", " << this->y << ") with " << this->argumentCount << " arguments and the executable path of " << executablePath << std::endl;
    for (int i = 0; i < this->argumentCount-1; i++) {
        std::cout << "Argument " << i+1 << ": " << this->arguments[i] << std::endl;
    }
}