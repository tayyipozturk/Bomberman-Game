#include "controller.h"

int main() {
    Parser parser = Parser();
    std::vector<Bomber> bombers = parser.getBombers();
    std::vector<Obstacle> obstacles = parser.getObstacles();
    std::vector<Bomb> bombs = std::vector<Bomb>();
    Map map = parser.getMap();
    std::vector<pid_t> bomber_pids;
    std::vector<pid_t> bomb_pids;

    int fd[bombers.size()][2];
    int** fd_bombs = nullptr;
    pipe_bombers(bombers.size(), fd);
    fork_bombers(bombers, fd, bomber_pids);
    poll(bombers, obstacles, bombs, map, fd, fd_bombs, bomber_pids, bomb_pids);
    reap_children(bomber_pids);
    reap_children(bomb_pids);



	return 0;
}