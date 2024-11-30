#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <time.h>

#define NUM_ITERATIONS 1000

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
    char* file_name_up;
    char* file_name_down;

    if (strcmp(mode, "local") == 0) {
        server_ip = "::1";
        file_name_up = "./logs/setup_local.csv";
        file_name_down = "./logs/teardown_local.csv";
    } else if (strcmp(mode, "remote") == 0){
        server_ip = remote_ip;
        file_name_up = "./logs/setup_remote.csv";
        file_name_down = "./logs/teardown_remote.csv";
    } else {
        perror("wrong mode, should be local or remote");
        exit(1);
    }

    struct sockaddr_in6 server_addr;
    struct timespec start_time, end_time;
    char buf[2];
    int c_fd;

    c_fd = socket(AF_INET6, SOCK_STREAM, 0);
    if (c_fd < 0) {
        perror("failed on socket");
        exit(EXIT_FAILURE);
    }

    FILE *f1 = fopen(file_name_up, "a");
    if (f1 == NULL) {
        perror("Failed to open log file");
        return 1;
    }
    FILE *f2 = fopen(file_name_down, "a");
    if (f2 == NULL) {
        perror("Failed to open log file");
        return 1;
    }

    server_addr.sin6_family = AF_INET6;
    server_addr.sin6_port = htons(port);
    inet_pton(AF_INET6, server_ip, &server_addr.sin6_addr);

    clock_gettime(CLOCK_MONOTONIC, &start_time);
    if (connect(c_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Failed Connection");
        close(c_fd);
        exit(1);
    }
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    double elapsed_time = ((end_time.tv_sec - start_time.tv_sec) * 1e9 +
                            (end_time.tv_nsec - start_time.tv_nsec));
    fprintf(f1, "%.2f\n", elapsed_time);

    int close_ret;

    clock_gettime(CLOCK_MONOTONIC, &start_time);
    if(close(c_fd) == -1){
        perror("Failed on close");
        exit(1);
    }
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    elapsed_time = ((end_time.tv_sec - start_time.tv_sec) * 1e9 +
                            (end_time.tv_nsec - start_time.tv_nsec));
    fprintf(f2, "%.2f\n", elapsed_time);
    close(c_fd);
    fclose(f1);
    fclose(f2);
    return 0;
}
