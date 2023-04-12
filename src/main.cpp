#include "controller.h"

int main() {
    Parser parser = Parser();
    std::vector<Bomber> bombers = parser.getBombers();
    std::vector<Obstacle> obstacles = parser.getObstacles();
    Map map = parser.getMap();

    int fd[bombers.size()][2];

    pipe_bombers(bombers.size(), fd);
    fork_bombers(bombers, fd);
    poll(bombers, obstacles, map, fd);


	return 0;
}