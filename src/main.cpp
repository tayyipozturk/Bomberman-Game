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
            dup2(fd[i][1], STDOUT_FILENO);
            close(fd[i][0]);
            for(int j =0; bomber.getArgs()[j] != NULL; j++) {
                std::cout<<bomber.getArgs()[j]<<std::endl;
            }
            execv(bomber.getArgs()[0], bomber.getArgs());

        }
        else {      //Controller
            close(fd[i][1]);
            close(fd[i][1]);
            // print messages coming to the pipe
            im incoming_message;
            while(1) {
                //polling poll kullan
                // if(poll>1){
                //     //read
                //}
                //else{
                //    no message
                //}
                //for(int i = 0; i < bombers.size(); i++){
                //    int poll(fd[i][1])
                //}


                read(fd[i][0], &incoming_message, sizeof(incoming_message));
                std::cout<<incoming_message.type<<std::endl;
                //std::cout<<incoming_message.data<<std::endl;
            //if(type == bomb.plant){
            //    fork()
             //   if(pid == 0){
                    //bomb
                    //explode
            //    }
            //    else{
                    //controller
                    //send bomb explode
            //    }
            }
        }
    }

	return 0;
}