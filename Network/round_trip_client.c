#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <time.h>

#define BUF_SIZE 512
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
    char* file_name;

    if (strcmp(mode, "local") == 0) {
        server_ip = "::1";
        file_name = "./logs/rtt_local.csv";
    } else if (strcmp(mode, "remote") == 0){
        server_ip = remote_ip;
        file_name = "./logs/rtt_remote.csv";
    } else {
        perror("wrong mode, should be local or remote");
        exit(1);
    }

    struct sockaddr_in6 server_addr;
    struct timespec start_time, end_time;
    char buf[BUF_SIZE];
    int c_fd;

    memset(buf, 'n', BUF_SIZE);
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
    int send_ret,recv_ret;
    FILE *f = fopen(file_name, "a");
    if (f == NULL) {
        perror("Failed to open log file");
        return 1;
    }
    double rtt[NUM_ITERATIONS];
    for (; i < NUM_ITERATIONS; i++){
        clock_gettime(CLOCK_MONOTONIC, &start_time);
        if((send_ret = send(c_fd, buf, BUF_SIZE, 0)) == -1){
            perror("failed on send");
		    close(c_fd);
            exit(1);
        }
        if((recv_ret =recv(c_fd, buf, BUF_SIZE, 0)) == -1){
            perror("failed on recv");
		    close(c_fd);
            exit(1);
        }
        clock_gettime(CLOCK_MONOTONIC, &end_time);
        double elapsed_time = ((end_time.tv_sec - start_time.tv_sec) * 1e9 +
                              (end_time.tv_nsec - start_time.tv_nsec));
        rtt[i] = elapsed_time;
        //fprintf(f, "%.2f\n",elapsed_time);
    }
    for (i = 0; i < NUM_ITERATIONS; i++) {
        fprintf(f, "%.2f\n", rtt[i]);
    }
    close(c_fd);
    fclose(f);
    return 0;
}
