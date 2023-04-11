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
        pid_t pid = fork();
        if (pid == 0) {
            Bomber bomber = bombers[i];
            close(fd[i][0]);
            dup2(fd[i][1], STDOUT_FILENO);
            close(fd[i][1]);
            execv(bomber.getArgs()[0], bomber.getArgs());
        }
        else {
            close(fd[i][1]);
            dup2(fd[i][0], STDIN_FILENO);
            close(fd[i][0]);
            // print messages coming to the pipe
            char buffer[1024];
            while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
                printf("%s", buffer);
            }
        }
    }

	return 0;
}