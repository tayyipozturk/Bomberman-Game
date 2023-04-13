#include "controller.h"

int main() {
    Parser parser = Parser();
    std::vector<Bomber> bombers = parser.getBombers();
    std::vector<Obstacle> obstacles = parser.getObstacles();
    std::vector<Bomb> bombs = std::vector<Bomb>();
    Map map = parser.getMap();
    std::vector<pid_t> pids;

    int fd[bombers.size()][2];
    pipe_bombers(bombers.size(), fd);
    fork_bombers(bombers, fd, pids);
    poll(bombers, obstacles, bombs, map, fd, pids);
    reap_children(pids);


	return 0;
}