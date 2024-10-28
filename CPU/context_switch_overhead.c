#include "../utils.h"
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <pthread.h>
#include <sys/wait.h>
#include <stdlib.h>

static int p[2];
struct timespec end_time;

double measure_process_switch_overhead(){
    nice(-20);
    struct timespec start_time, end_time;
    int p[2];
    if (pipe(p) < 0) {
        perror("Failed to create pipe");
    }
    if (write(p[1], "a", 1) == -1){
            perror("failed to write to pipe");
    }
    int pid = fork();
    char readbuf;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start_time);
    if(pid == -1){
        perror("fork failed");
        exit(1);
    } else if (pid == 0){
        clock_gettime(CLOCK_MONOTONIC_RAW, &start_time);
        if (read(p[0], &readbuf, 1) == -1) {
            perror("failed pipe read");
        }
        exit(0);
    } else {
        wait(NULL);
        clock_gettime(CLOCK_MONOTONIC_RAW, &end_time);
    }
    double elapsed_time = ((end_time.tv_sec - start_time.tv_sec) * 1e9 +
                              (end_time.tv_nsec - start_time.tv_nsec));
    FILE *f = fopen("./logs/process_switch_overhead.csv", "a");
    if (f == NULL) {
        perror("Failed to open log file");
        return 1;
    }
    fprintf(f, "%.2f\n",elapsed_time);
    return elapsed_time;
}

void * dummy_thread(void* args) {
    clock_gettime(CLOCK_MONOTONIC_RAW, &end_time);
    if (write(p[1], "a", 1) == -1){
        perror("failed to write to pipe");
    }
    return NULL;
}

// used https://stackoverflow.com/questions/965316/how-can-unix-pipes-be-used-between-main-process-and-thread
// as guidance of writing the dummy thread
double measure_thread_switch_overhead(){
    nice(-20);
    struct timespec start_time;
    if (pipe(p) < 0) {
        perror("Failed to create pipe");
    }
    if (write(p[1], "a", 1) == -1){
        perror("failed to write to pipe");
    }
    pthread_t tid;
    char readbuf;
    pthread_create(&tid, NULL, dummy_thread, NULL);
    clock_gettime(CLOCK_MONOTONIC_RAW, &start_time);
    read(p[0], &readbuf, sizeof(int));
    pthread_join(tid, NULL);
    double elapsed_time = ((end_time.tv_sec - start_time.tv_sec) * 1e9 +
                              (end_time.tv_nsec - start_time.tv_nsec));
    FILE *f = fopen("./logs/thread_switch_overhead.csv", "a");
    if (f == NULL) {
        perror("Failed to open log file");
        return 1;
    }
    fprintf(f, "%.2f\n",elapsed_time);
    return elapsed_time;
}

int main() {
    measure_process_switch_overhead();
    measure_thread_switch_overhead();
    return 0;
}
