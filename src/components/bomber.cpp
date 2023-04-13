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

void Bomber::Start(int socket, Map& map, omp* omp) {
    map.setBomber(this->getX(), this->getY());
    omp->m->type = BOMBER_LOCATION;
    omp->m->data.new_position.x = this->getX();
    omp->m->data.new_position.y = this->getY();
    send_message(socket, omp->m);
    print_output(NULL, omp, NULL, NULL);
}

void Bomber::Vision(int socket, Map& map, omp* omp, std::vector<Bomber>& bombers, std::vector<Obstacle>& obstacles, std::vector<Bomb>& bombs) {
    std::vector<od> vision = getVision(bombers, obstacles, bombs);
    od* objects = (od*) malloc(sizeof(od) * vision.size());
    for (int i=0 ; i < vision.size() ; i++) {
        objects[i] = vision[i];
    }

    omp->m->type = BOMBER_VISION;
    omp->m->data.object_count = vision.size();
    send_message(socket, omp->m);
    send_object_data(socket, vision.size(), objects);
    print_output(NULL, omp, NULL, objects);
}

std::vector<od> Bomber::getVision(std::vector<Bomber>& bombers, std::vector<Obstacle>& obstacles, std::vector<Bomb>& bombs) {
    std::vector<od> vision;
    int min_x = x - 3;
    int max_x = x + 3;
    int min_y = y - 3;
    int max_y = y + 3;

    for (int i=0 ; i < bombers.size() ; i++) {
        if (bombers[i].getX() >= min_x && bombers[i].getX() <= max_x && bombers[i].getY() == this->getY() && bombers[i].getX() != this->getX()) {
            od object;
            object.type = BOMBER;
            object.position.x = bombers[i].getX();
            object.position.y = bombers[i].getY();
            vision.push_back(object);
        }
        else if (bombers[i].getY() >= min_y && bombers[i].getY() <= max_y && bombers[i].getX() == this->getX() && bombers[i].getY() != this->getY()) {
            od object;
            object.type = BOMBER;
            object.position.x = bombers[i].getX();
            object.position.y = bombers[i].getY();
            vision.push_back(object);
        }
    }

    for (int i=0 ; i < obstacles.size() ; i++) {
        if (obstacles[i].getX() >= min_x && obstacles[i].getX() <= max_x && obstacles[i].getY() == this->getY()) {
            od object;
            object.type = OBSTACLE;
            object.position.x = obstacles[i].getX();
            object.position.y = obstacles[i].getY();
            vision.push_back(object);
        }
        else if (obstacles[i].getY() >= min_y && obstacles[i].getY() <= max_y && obstacles[i].getX() == this->getX()) {
            od object;
            object.type = OBSTACLE;
            object.position.x = obstacles[i].getX();
            object.position.y = obstacles[i].getY();
            vision.push_back(object);
        }
    }
    return vision;
}