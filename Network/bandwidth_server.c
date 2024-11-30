#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>

#define PORT 1702
#define BUF_SIZE (1024*1024*1024) // 1GB
#define NUM_ITERATIONS 10

double calculate_gbps(double time_ns, int data_size_bytes) {
    // Convert data size from bytes to bits
    double data_size_bits = data_size_bytes/BUF_SIZE * 8.0;
    double time_sec = time_ns / 1e9;
    double gbps = data_size_bits / time_sec;
    return gbps;
}

void print_usage(const char *prog_name) {
    printf("Usage: %s <localx|remote> \n", prog_name);
}

int main(int argc, char *argv[]) {
    char * file_name;
    const char* mode = argv[1];
    if (strcmp(mode, "local") == 0) {
        file_name = "./logs/bandwidth_local.csv";
    } else if (strcmp(mode, "remote") == 0){
        file_name = "./logs/bandwidth_remote.csv";
    } else {
        perror("wrong mode, should be local or remote");
        exit(1);
    }

    nice(-20);
    int s_fd, c_fd;
    struct sockaddr_in6 address;
    char* buf = malloc(BUF_SIZE);
    struct timespec start_time, end_time;
    int opt = 1;

    if ((s_fd = socket(AF_INET6, SOCK_STREAM, 0)) < 0) {
        perror("Failed on socket");
        free(buf);
        exit(1);
    }
    setsockopt(s_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    address.sin6_family = AF_INET6;
    address.sin6_addr = in6addr_any;
    address.sin6_port = htons(PORT);

    if (bind(s_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Failed on bind");
        free(buf);
        exit(1);
    }
    double bw[NUM_ITERATIONS];
    int recv_ret;
    int i = 0;

    FILE *f = fopen(file_name, "a");
    if (f == NULL) {
        perror("Failed to open log file");
        return 1;
    }

    listen(s_fd, 10);
    printf("Server up on port %d...\n", PORT);
    if((c_fd = accept(s_fd, NULL, NULL)) < 0){
        perror("Failed on accept");
        free(buf);
        close(s_fd);
        exit(1);
    }
    for (; i < NUM_ITERATIONS; i++) {
        int total_bytes = 0;
        clock_gettime(CLOCK_MONOTONIC, &start_time);
        while (total_bytes < BUF_SIZE) {
            recv_ret = recv(c_fd, buf + total_bytes, BUF_SIZE - total_bytes, 0);
            if (recv_ret <= 0) {
                perror("Failed on recv");
                free(buf);
                close(c_fd);
                close(s_fd);
                exit(1);
            }
            total_bytes += recv_ret;
        }
        if (total_bytes != BUF_SIZE) {
            printf("Error: Expected %d bytes, received %d bytes only\n", BUF_SIZE, total_bytes);
            free(buf);
            close(c_fd);
            close(s_fd);
            exit(1);
        }
        clock_gettime(CLOCK_MONOTONIC, &end_time);
        printf("end time %0.2f for iter %i\n",end_time.tv_sec* 1e9+end_time.tv_nsec, i);
        double elapsed_time = ((end_time.tv_sec - start_time.tv_sec) * 1e9 +
                            (end_time.tv_nsec - start_time.tv_nsec));
        bw[i] = elapsed_time;
    }

    for (int i = 0; i < NUM_ITERATIONS; i++) {
        printf("bandwith for iter %i: %0.2f\n",i,calculate_gbps(bw[i],BUF_SIZE));
        fprintf(f, "%.2f\n", bw[i]);
    }
    close(s_fd);
    close(c_fd);
    free(buf);
    return 0;
}