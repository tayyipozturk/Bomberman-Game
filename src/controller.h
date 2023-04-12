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

#define PIPE(fd) socketpair(AF_UNIX, SOCK_STREAM, PF_UNIX, fd)