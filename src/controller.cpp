#include "controller.h"

void pipe_bombers(int size, int fd[][2]) {
    for (int i = 0; i < size; i++) {
        PIPE(fd[i]);
    }
}

void fork_bombers(std::vector<Bomber>& bombers, int fd[][2], std::vector<pid_t>& pids) {
    for (int i = 0; i < bombers.size(); i++) {
        Bomber bomber = bombers[i];
        pid_t pid = fork();
        pids.push_back(pid);
        if (pid == 0) {
            dup2(fd[i][0], STDIN_FILENO);
            dup2(fd[i][0], STDOUT_FILENO);
            close(fd[i][0]);
            execv(bomber.getArgs()[0], bomber.getArgs());
        }
        else {
            close(fd[i][0]);
            dup2(fd[i][1], STDIN_FILENO);
        }
    }
}

void poll(std::vector<Bomber>& bombers, std::vector<Obstacle>& obstacles, std::vector<Bomb>& bombs, Map& map, int fd[][2], std::vector<pid_t>& pids) {
    imp imp;
    im im;
    omp omp;
    om om;
    omp.m = &om;
    //create pfd arrays for each pipe
    struct pollfd pfd[bombers.size()];
    for (int j = 0; j < bombers.size(); j++) {
        pfd[j].fd = fd[j][1];
        pfd[j].events = POLLIN;
        pfd[j].revents = 0;
    }
    int timeout = 1000;  // timeout in milliseconds
    while (Bomber::aliveCount > 1) {
        int num_events = poll(pfd, bombers.size(), timeout);
        if (num_events > 0) {
            for (int j = 0; j < bombers.size(); j++) {
                if (pfd[j].revents & POLLIN) {
                    read_data(fd[j][1], &im);
                    imp.pid = pids[j];
                    imp.m = &im;
                    print_output(&imp, NULL, NULL, NULL);
                    if (im.type == BOMBER_START) {
                        omp.pid = pids[j];
                        bombers[j].Start(fd[j][1], map, &omp);
                    }
                     else if (im.type == BOMBER_SEE) {
                        omp.pid = pids[j];
                        bombers[j].See(fd[j][1], map, &omp, bombers, obstacles, bombs);
                    }
                    else if (im.type == BOMBER_MOVE) {
                        omp.pid = pids[j];
                        coordinate target = im.data.target_position;
                        bombers[j].Move(fd[j][1], map, &omp, bombers, obstacles, bombs, target);
                    }
                    else if (im.type == BOMBER_PLANT) {
                        //bomber.plant(incoming_message.data.bomb_info.interval, incoming_message.data.bomb_info.radius);
                    }
                    else if (im.type == BOMB_EXPLODE) {
                        //bomber.explode();
                    }
                }
            }
        }
    }
}

void reap_children(std::vector<pid_t>& pids) {
    for (int i = 0; i < pids.size(); i++) {
        waitpid(pids[i], NULL, 0);
    }
}
