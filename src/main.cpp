#include "controller.h"

int main() {
    Parser parser = Parser();
    std::vector<Bomber> bombers = parser.getBombers();
    std::vector<Obstacle> obstacles = parser.getObstacles();
    Map map = parser.getMap();

    int fd[bombers.size()][2];
    for (int i = 0; i < bombers.size(); i++) {
        PIPE(fd[i]);
    }

    for (int i = 0; i < bombers.size(); i++) {
        Bomber bomber = bombers[i];
        pid_t pid = fork();
        if (pid == 0) {
            dup2(fd[i][0], STDIN_FILENO);
            dup2(fd[i][0], STDOUT_FILENO);
            close(fd[i][0]);
            for(int j =0; bomber.getArgs()[j] != NULL; j++) {
                std::cout<<bomber.getArgs()[j]<<std::endl;
            }
            execv(bomber.getArgs()[0], bomber.getArgs());

        }
        else {      //Controller
            close(fd[i][0]);
            dup2(fd[i][1], STDIN_FILENO);
            // print messages coming to the pipe
            im incoming_message;
            //create pollfd arrays for each pipe
            struct pollfd pfd[bombers.size()];
            for(int j = 0; j < bombers.size(); j++){
                pfd[j].fd = fd[j][1];
                pfd[j].events = POLLIN;
                pfd[j].revents = 0;
            }
            int timeout = 1000;  // timeout in milliseconds
            while(Bomber::aliveCount > 1){
                int num_events = poll(pfd, bombers.size(), timeout);
                if(num_events > 0){
                    for(int j = 0; j < bombers.size(); j++){
                        if(pfd[j].revents & POLLIN){
                            read_data(fd[j][1], &incoming_message);
                            imp incoming_message_print;
                            incoming_message_print.pid = pid;
                            incoming_message_print.m = &incoming_message;
                            print_output(&incoming_message_print, NULL, NULL, NULL);
                        }
                    }
                }
            }
        }
    }

	return 0;
}