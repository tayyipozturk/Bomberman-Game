#include "controller.h"

void pipe_bombers(int size, int fd[][2]) {
    for (int i = 0; i < size; i++) {
        PIPE(fd[i]);
    }
}

void fork_bombers(std::vector<Bomber> bombers, int fd[][2]) {
    for (int i = 0; i < bombers.size(); i++) {
        Bomber bomber = bombers[i];
        pid_t pid = fork();
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

void poll(std::vector<Bomber> bombers, std::vector<Obstacle> obstacles, Map map, int fd[][2]) {
    im incoming_message;
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
                    read_data(fd[j][1], &incoming_message);
                    imp incoming_message_print;
                    incoming_message_print.pid = getpid();
                    incoming_message_print.m = &incoming_message;
                    print_output(&incoming_message_print, NULL, NULL, NULL);
                    if (incoming_message.type == BOMBER_MOVE) {
                        //bomber.move(incoming_message.data.target_position);
                    } else if (incoming_message.type == BOMBER_SEE) {
                        bombers[j].Vision(fd[j][1], map);
                    } else if (incoming_message.type == BOMBER_START) {
                        bombers[j].Start(fd[j][1]);
                    } else if (incoming_message.type == BOMBER_PLANT) {
                        //bomber.plant(incoming_message.data.bomb_info.interval, incoming_message.data.bomb_info.radius);
                    } else if (incoming_message.type == BOMB_EXPLODE) {
                        //bomber.explode();
                    }
                }
            }
        }
    }
}