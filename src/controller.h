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
#include "components/bomber.h"
#include "components/obstacle.h"
#include "components/bomb.h"
#include "components/map.h"

#define PIPE(fd) socketpair(AF_UNIX, SOCK_STREAM, PF_UNIX, fd)

void pipe_bombers(int n, int fd[][2]);
void fork_bombers(std::vector<Bomber>& bombers, int fd[][2], std::vector<pid_t>& pids);
void poll(std::vector<Bomber>& bombers, std::vector<Obstacle>& obstacles, std::vector<Bomb>& bombs, Map& map, int fd[][2], std::vector<pid_t>& pids);
void reap_children(std::vector<pid_t>& pids);

#endif //CONTROLLER_H