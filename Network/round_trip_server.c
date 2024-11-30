#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 1701
#define BUF_SIZE 512
#define NUM_ITERATIONS 100
//https://www.geeksforgeeks.org/socket-programming-cc/


int main() {
    nice(-20);
    int s_fd, c_fd;
    struct sockaddr_in6 address;
    char buf[BUF_SIZE];
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

    listen(s_fd, 10);
    memset(buf, 'n', BUF_SIZE);
    printf("Server up on port %d...\n", PORT);
    if((c_fd = accept(s_fd, NULL, NULL)) < 0){
        perror("Failed on accept");
        exit(1);
    }
    // Accept and echo data
    int i = 0;
    for (; i < NUM_ITERATIONS; i++){
        recv(c_fd, buf, BUF_SIZE, 0);
        send(c_fd, buf, BUF_SIZE, 0);
    }
    close(s_fd);
    return 0;
}
