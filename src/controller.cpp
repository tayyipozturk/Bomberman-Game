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
        if (pid == 0) {
            //close(fd[i][1]);
            dup2(fd[i][0], STDIN_FILENO);
            dup2(fd[i][0], STDOUT_FILENO);
            close(fd[i][0]);
            execv(bomber.getArgs()[0], bomber.getArgs());
        }
        else {
            pids.push_back(pid);
            close(fd[i][0]);
            dup2(fd[i][1], STDIN_FILENO);
            //close(fd[i][1]);
        }
    }
}

void poll(std::vector<Bomber>& bombers, std::vector<Obstacle>& obstacles, std::vector<Bomb>& bombs, Map& map, int fd[][2], int** fd_bombs, std::vector<pid_t>& pids, std::vector<pid_t>& bomb_pids) {
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
    // create pfd array for bombs
    struct pollfd* pfd_bombs = nullptr;

    int timeout = 1000;  // timeout in milliseconds
    while (Bomber::aliveCount > 0) {
        int bomb_events = poll(pfd_bombs, bombs.size(), timeout);
        if (bomb_events > 0) {
            for (int j = 0; j < bombs.size(); j++) {
                if (pfd_bombs[j].revents & POLLIN) {
                    read_data(fd_bombs[j][1], &im);
                    imp.pid = pids[j];
                    imp.m = &im;
                    print_output(&imp, NULL, NULL, NULL);
                    if (im.type == BOMB_EXPLODE) {
                        std::vector<Bomber> bomberToBeRemoved;
                        std::vector<Obstacle> obstacleToBeRemoved;
                        std::vector<od> targetObjects = bombs[j].getVision(bombs[j].getRadius(), map);
                        for (auto& targetObject : targetObjects) {
                            if (targetObject.type == BOMBER) {
                                for (int i = bombers.size()-1; i>=0; i--) {
                                    if (Bomber::aliveCount == 1) {
                                        break;
                                    }
                                    if (bombers[i].getX() == targetObject.position.x && bombers[i].getY() == targetObject.position.y) {
                                        bombers[i].setIsAlive(false);
                                        bomberToBeRemoved.push_back(bombers[i]);
                                    }
                                }
                            } else if (targetObject.type == OBSTACLE) {
                                for (int i = obstacles.size()-1; i>=0; i--) {
                                    if (obstacles[i].getX() == targetObject.position.x && obstacles[i].getY() == targetObject.position.y) {
                                        if (obstacles[i].getDurability() != -1){
                                            obstacles[i].setDurability(obstacles[i].getDurability() - 1);
                                            if (obstacles[i].getDurability() == 0) {
                                                obstacleToBeRemoved.push_back(obstacles[i]);
                                                obstacles.erase(obstacles.begin() + i);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        bombs[j].setIsLive(false);
                        if(map.getOccupancy(bombs[j].getX(), bombs[j].getY()) == BOMB_OBJ){
                            map.setEmpty(bombs[j].getX(), bombs[j].getY());
                        }
                        else if(map.getOccupancy(bombs[j].getX(), bombs[j].getY()) == BOMBER_AND_BOMB){
                            map.setBomber(bombs[j].getX(), bombs[j].getY());
                        }

                        for (auto& bomber : bomberToBeRemoved) {
                            if (map.getOccupancy(bomber.getX(), bomber.getY()) == BOMBER_OBJ) {
                                map.setEmpty(bomber.getX(), bomber.getY());
                            }
                            else if (map.getOccupancy(bomber.getX(), bomber.getY()) == BOMBER_AND_BOMB) {
                                map.setBomb(bomber.getX(), bomber.getY());
                            }
                        }

                        for (auto& obstacle : obstacleToBeRemoved) {
                            map.setEmpty(obstacle.getX(), obstacle.getY());
                        }
                    }
                }
            }
        }

        int num_events = poll(pfd, bombers.size(), timeout);
        if (num_events > 0) {
            for (int j = 0; j < bombers.size(); j++) {
                if (pfd[j].revents & POLLIN) {
                    read_data(fd[j][1], &im);
                    imp.pid = pids[j];
                    imp.m = &im;
                    print_output(&imp, NULL, NULL, NULL);
                    if (Bomber::aliveCount == 1 && bombers[j].getIsAlive()) {
                        omp.pid = pids[j];
                        om.type = BOMBER_WIN;
                        send_message(fd[j][1], &om);
                        print_output(NULL, &omp, NULL, NULL);
                        goto end;
                    }
                    if (!bombers[j].getIsAlive()) {
                        omp.pid = pids[j];
                        om.type = BOMBER_DIE;
                        send_message(fd[j][1], &om);
                        print_output(NULL, &omp, NULL, NULL);
                    }
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
                        if (map.getOccupancy(bombers[j].getX(), bombers[j].getY()) != BOMB_OBJ || map.getOccupancy(bombers[j].getX(), bombers[j].getY()) != BOMBER_AND_BOMB){
                            long interval = im.data.bomb_info.interval;
                            unsigned int radius = im.data.bomb_info.radius;
                            char timer[32];
                            sprintf(timer, "%ld", interval);
                            // add bomb object to the bombs vector
                            Bomb bomb = Bomb(bombers[j].getX(), bombers[j].getY(), radius, interval);
                            bombs.push_back(bomb);
                            map.setBomberAndBomb(bombers[j].getX(), bombers[j].getY());
                            fd_bombs = (int**) realloc(fd_bombs, bombs.size() * sizeof(int*));
                            fd_bombs[bombs.size() - 1] = (int*) malloc(2 * sizeof(int));
                            PIPE(fd_bombs[bombs.size() - 1]);
                            pfd_bombs = (struct pollfd*) realloc(pfd_bombs, bombs.size() * sizeof(struct pollfd));
                            pfd_bombs[bombs.size() - 1].fd = fd_bombs[bombs.size() - 1][1];
                            pfd_bombs[bombs.size() - 1].events = POLLIN;
                            pfd_bombs[bombs.size() - 1].revents = 0;
                            pid_t pid = fork();
                            if (pid == 0) {
                                std::string file = "./bomb";
                                char** args = (char**) malloc(3 * sizeof(char*));
                                args[0] = (char*) malloc(file.length() + 1);
                                strcpy(args[0], file.c_str());
                                args[1] = (char*) malloc(strlen(timer) + 1);
                                strcpy(args[1], timer);
                                args[2] = NULL;

                                //close(fd_bombs[bombs.size() - 1][1]);
                                dup2(fd_bombs[bombs.size() - 1][0], STDIN_FILENO);
                                dup2(fd_bombs[bombs.size() - 1][0], STDOUT_FILENO);
                                close(fd_bombs[bombs.size() - 1][0]);

                                execv(args[0], args);
                            }
                            else {
                                bomb_pids.push_back(pid);
                                close(fd_bombs[bombs.size() - 1][0]);
                                dup2(fd_bombs[bombs.size() - 1][1], STDIN_FILENO);
                                //close(fd_bombs[bombs.size() - 1][1]);
                                omp.pid = pids[j];
                                omp.m->type = BOMBER_PLANT_RESULT;
                                omp.m->data.planted = 1;
                                send_message(fd[j][1], omp.m);
                                print_output(NULL, &omp, NULL, NULL);
                            }
                        }
                        else{
                            omp.pid = pids[j];
                            omp.m->type = BOMBER_PLANT_RESULT;
                            omp.m->data.planted = 0;
                            send_message(fd[j][1], omp.m);
                            print_output(NULL, &omp, NULL, NULL);
                        }

                    }
                }
            }
        }
        sleep(1);
    }
    end:
    int p = 0;
}

void reap_children(std::vector<pid_t>& pids) {
    for (int i = 0; i < pids.size(); i++) {
        waitpid(pids[i], NULL, 0);
    }
}
