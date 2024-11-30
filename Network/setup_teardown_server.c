#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>

#define PORT 1703

int main() {
    nice(-20);
    int s_fd, c_fd;
    struct sockaddr_in6 address;
    char buf[2];
    int opt = 1;

    if ((s_fd = socket(AF_INET6, SOCK_STREAM, 0)) < 0) {
        perror("Failed on socket");
        exit(1);
    }
    setsockopt(s_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    address.sin6_family = AF_INET6;
    address.sin6_addr = in6addr_any;
    address.sin6_port = htons(PORT);

    if (bind(s_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Failed on bind");
        exit(1);
    }
    int recv_ret;
    int i = 0;

    listen(s_fd, 10);
    printf("Server up on port %d...\n", PORT);
    if((c_fd = accept(s_fd, NULL, NULL)) < 0){
        perror("Failed on accept");
        close(s_fd);
        exit(1);
    }
    while (1) {
        continue;
    }
    close(s_fd);
    close(c_fd);
    return 0;
}