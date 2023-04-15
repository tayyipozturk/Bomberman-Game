#include "bomber.h"

int Bomber::aliveCount = 0;
int Bomber::dieLog = 0;

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
    if (isAlive && !this->isAlive) {
        aliveCount++;
    } else if (!isAlive && this->isAlive) {
        aliveCount--;
    }
    this->isAlive = isAlive;
}

bool Bomber::getIsAlive() {
    return this->isAlive;
}

void Bomber::Start(int socket, Map& map, omp* omp) {
    map.setBomber(this->getX(), this->getY());
    omp->m->type = BOMBER_LOCATION;
    omp->m->data.new_position.x = this->getX();
    omp->m->data.new_position.y = this->getY();
    send_message(socket, omp->m);
    print_output(NULL, omp, NULL, NULL);
}

void Bomber::See(int socket, Map& map, omp* omp) {
    std::vector<od> vision = getVision(map);
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

std::vector<od> Bomber::getVision(Map &map) {
    std::vector<od> vision;
    bool up, down, left, right;                                     // flags to check if a way is blocked by an obstacle
    up = down = left = right = true;

    for (int i = 1; i <= 3; i++) {
        if (up && this->y - i >= 0) {
            od object;
            object.position.x = this->x;
            object.position.y = this->y - i;
            if (map.getOccupancy(this->x, this->y - i) == BOMB_OBJ){
                object.type = BOMB;
            }
            else if (map.getOccupancy(this->x, this->y - i) == BOMBER_OBJ){
                object.type = BOMBER;
            }
            else if (map.getOccupancy(this->x, this->y - i) == OBSTACLE_OBJ){
                object.type = OBSTACLE;
                up = false;
            }
            else if (map.getOccupancy(this->x, this->y - i) == BOMBER_AND_BOMB){
                object.type = BOMB;
                od object2;
                object2.position.x = this->x;
                object2.position.y = this->y - i;
                object2.type = BOMBER;
                vision.push_back(object2);
            }
            else{
                continue;
            }
            vision.push_back(object);
        }
    }

    for (int i = 1; i <= 3; i++) {
        if (down && this->y + i < map.getHeight()) {
            od object;
            object.position.x = this->x;
            object.position.y = this->y + i;
            if (map.getOccupancy(this->x, this->y + i) == BOMB_OBJ){
                object.type = BOMB;
            }
            else if (map.getOccupancy(this->x, this->y + i) == BOMBER_OBJ){
                object.type = BOMBER;
            }
            else if (map.getOccupancy(this->x, this->y + i) == OBSTACLE_OBJ){
                object.type = OBSTACLE;
                down = false;
            }
            else if (map.getOccupancy(this->x, this->y + i) == BOMBER_AND_BOMB){
                object.type = BOMB;
                od object2;
                object2.position.x = this->x;
                object2.position.y = this->y + i;
                object2.type = BOMBER;
                vision.push_back(object2);
            }
            else{
                continue;
            }
            vision.push_back(object);
        }
    }

    for (int i = 1; i <= 3; i++) {
        if (left && this->x - i >= 0) {
            od object;
            object.position.x = this->x - i;
            object.position.y = this->y;
            if (map.getOccupancy(this->x - i, this->y) == BOMB_OBJ){
                object.type = BOMB;
            }
            else if (map.getOccupancy(this->x - i, this->y) == BOMBER_OBJ){
                object.type = BOMBER;
            }
            else if (map.getOccupancy(this->x - i, this->y) == OBSTACLE_OBJ){
                object.type = OBSTACLE;
                left = false;
            }
            else if (map.getOccupancy(this->x - i, this->y) == BOMBER_AND_BOMB){
                object.type = BOMB;
                od object2;
                object2.position.x = this->x - i;
                object2.position.y = this->y;
                object2.type = BOMBER;
                vision.push_back(object2);
            }
            else{
                continue;
            }
            vision.push_back(object);
        }
    }

    for (int i = 1; i <= 3; i++) {
        if (right && this->x + i < map.getWidth()) {
            od object;
            object.position.x = this->x + i;
            object.position.y = this->y;
            if (map.getOccupancy(this->x + i, this->y) == BOMB_OBJ){
                object.type = BOMB;
            }
            else if (map.getOccupancy(this->x + i, this->y) == BOMBER_OBJ){
                object.type = BOMBER;
            }
            else if (map.getOccupancy(this->x + i, this->y) == OBSTACLE_OBJ){
                object.type = OBSTACLE;
                right = false;
            }
            else if (map.getOccupancy(this->x + i, this->y) == BOMBER_AND_BOMB){
                object.type = BOMB;
                od object2;
                object2.position.x = this->x + i;
                object2.position.y = this->y;
                object2.type = BOMBER;
                vision.push_back(object2);
            }
            else{
                continue;
            }
            vision.push_back(object);
        }
    }
    return vision;
}

void Bomber::Move(int socket, Map& map, omp* omp, std::vector<Bomber>& bombers, std::vector<Obstacle>& obstacles, std::vector<Bomb>& bombs, coordinate target){
    int target_x = target.x;
    int target_y = target.y;
    if (target_x == this->x && (target_y == this->y+1 || target_y== this->y-1)
            && (target_y >=0 && target_y < map.getHeight())
            && (map.getOccupancy(target_x, target_y) == EMPTY || map.getOccupancy(target_x, target_y) == BOMB_OBJ)){
        omp->m->type = BOMBER_LOCATION;
        omp->m->data.new_position.x = target_x;
        omp->m->data.new_position.y = target_y;

        if (map.getOccupancy(target_x, target_y) == BOMB_OBJ) {
            map.setBomberAndBomb(target_x, target_y);
        } else {
            map.setBomber(target_x, target_y);
        }

        if (map.getOccupancy(this->x, this->y) == BOMBER_AND_BOMB) {
            map.setBomb(this->x, this->y);
        } else {
            map.setEmpty(this->x, this->y);
        }
        this->x = target_x;
        this->y = target_y;
        send_message(socket, omp->m);
        print_output(NULL, omp, NULL, NULL);
        return;
    }
    else if (target_y == this->y && (target_x == this->x+1 || target_x == this->x-1)
            && (target_x >=0 && target_x < map.getWidth())
            && (map.getOccupancy(target_x, target_y) == EMPTY || map.getOccupancy(target_x, target_y) == BOMB_OBJ)){
        omp->m->type = BOMBER_LOCATION;
        omp->m->data.new_position.x = target_x;
        omp->m->data.new_position.y = target_y;

        if (map.getOccupancy(target_x, target_y) == BOMB_OBJ) {
            map.setBomberAndBomb(target_x, target_y);
        } else {
            map.setBomber(target_x, target_y);
        }

        if (map.getOccupancy(this->x, this->y) == BOMBER_AND_BOMB) {
            map.setBomb(this->x, this->y);
        } else {
            map.setEmpty(this->x, this->y);
        }
        this->x = target_x;
        this->y = target_y;
        send_message(socket, omp->m);
        print_output(NULL, omp, NULL, NULL);
        return;
    }
    else{
        omp->m->type = BOMBER_LOCATION;
        omp->m->data.new_position.x = this->x;
        omp->m->data.new_position.y = this->y;
        send_message(socket, omp->m);
        print_output(NULL, omp, NULL, NULL);
        return;
    }
}