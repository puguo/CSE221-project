#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <time.h>

#define BUF_SIZE (1024*1024*1024) // 1GB
#define NUM_ITERATIONS 10

void print_usage(const char *prog_name) {
    printf("Usage: %s <local|remote> <port> <remote_ip>\n", prog_name);
}

int main(int argc, char *argv[]) {
    nice(-20);
    if (argc != 4) {
        print_usage(argv[0]);
        exit(1);
    }
    const char* mode = argv[1];
    int port = atoi(argv[2]);
    char* remote_ip = argv[3];
    char* server_ip;
    char* file_name;

    if (strcmp(mode, "local") == 0) {
        server_ip = "::1";
        file_name = "./logs/bandwidth_local.csv";
    } else if (strcmp(mode, "remote") == 0){
        server_ip = remote_ip;
        file_name = "./logs/bandwidth_remote.csv";
    } else {
        perror("wrong mode, should be local or remote");
        exit(1);
    }

    struct sockaddr_in6 server_addr;
    char* buf = malloc(BUF_SIZE);
    int c_fd;

    c_fd = socket(AF_INET6, SOCK_STREAM, 0);
    if (c_fd < 0) {
        perror("failed on socket");
        exit(EXIT_FAILURE);
    }

    server_addr.sin6_family = AF_INET6;
    server_addr.sin6_port = htons(port);
    inet_pton(AF_INET6, server_ip, &server_addr.sin6_addr);

    if (connect(c_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Failed Connection");
        close(c_fd);
        exit(1);
    }

    int i = 0;
    int send_ret;
    struct timespec start_time;
    FILE *f = fopen(file_name, "a");
    if (f == NULL) {
        perror("Failed to open log file");
        return 1;}
    for (; i < NUM_ITERATIONS; i++){
        memset(buf, i % NUM_ITERATIONS, BUF_SIZE);
        clock_gettime(CLOCK_MONOTONIC, &start_time);
        if((send_ret = send(c_fd, buf, BUF_SIZE, 0)) == -1){
            perror("failed on send");
            free(buf);
		    close(c_fd);
            exit(1);
        }
        printf("start time %0.2f for iter %i\n",start_time.tv_sec* 1e9+start_time.tv_nsec, i);
    }
    free(buf);
    close(c_fd);
    return 0;
}
