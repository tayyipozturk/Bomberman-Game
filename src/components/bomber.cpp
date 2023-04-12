#include "bomber.h"

Bomber::Bomber(int x, int y, int argumentCount, char** arguments) {
    this->x = x;
    this->y = y;
    this->argumentCount = argumentCount;
    this->args = arguments;
    this->isAlive = true;
    aliveCount++;
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

char** Bomber::getArgs() {
    return this->args;
}

void Bomber::setIsAlive(bool isAlive) {
    this->isAlive = isAlive;
    if (isAlive) {
        aliveCount++;
    } else {
        aliveCount--;
    }
}

bool Bomber::getIsAlive() {
    return this->isAlive;
}

int Bomber::aliveCount = 0;

void Bomber::Start(int socket) {
    om out_message;
    out_message.type = BOMBER_LOCATION;
    out_message.data.new_position.x = this->getX();
    out_message.data.new_position.y = this->getY();
    send_message(socket, &out_message);
}

void Bomber::Vision(int socket, Map map) {
    om out_message;
    out_message.type = BOMBER_VISION;
    out_message.data.object_count = map.getVision(this->getX(), this->getY());
    send_message(socket, &out_message);
}