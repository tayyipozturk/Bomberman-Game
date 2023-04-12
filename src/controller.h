#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <sys/socket.h>
#include <sys/wait.h>
#include <iostream>
#include "parser.h"
extern "C" {
    #include <unistd.h>
}
extern "C" {
    #include "logging.h"
}
#include <vector>
#include <string>
#include <poll.h>

#define PIPE(fd) socketpair(AF_UNIX, SOCK_STREAM, PF_UNIX, fd)

void pipe_bombers(int n, int fd[][2]);
void fork_bombers(std::vector<Bomber> bombers, int fd[][2]);
void poll(std::vector<Bomber> bombers, std::vector<Obstacle> obstacles, Map map, int fd[][2]);


#endif //CONTROLLER_H