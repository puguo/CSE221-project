#include "../utils.h"
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <pthread.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#define NUM_ITERATIONS 10000

int p1[2], p2[2];

double measure_process_switch_overhead(){
    nice(-20);
    int p1[2], p2[2];
    struct timespec start_time,end_time;
    char readbuf;
    if (pipe(p1) < 0 || pipe(p2)<0) {
        perror("Failed to create pipe");
    }

    int pid = fork();
    nice(-20);
    if(pid == -1){
        perror("fork failed");
        exit(1);
    } else if (pid == 0) { // Child process
        for (int i = 0; i < NUM_ITERATIONS; i++) {
            if (read(p1[0], &readbuf, 1) != 1) {
                perror("Child failed to read");
                exit(1);
            }
            if (write(p2[1], "a", 1) != 1) {
                perror("Child failed to write");
                exit(1);
            }
        }
        exit(0);
    } else { // Parent process
        clock_gettime(CLOCK_MONOTONIC_RAW, &start_time);
        for (int i = 0; i < NUM_ITERATIONS; i++) {
            if (write(p1[1], "a", 1) == -1) {
                perror("Parent failed to write");
                exit(1);
            }
            if (read(p2[0], &readbuf, 1) != 1) {
                perror("Parent  failed to read");
                exit(1);
            }
        }
        clock_gettime(CLOCK_MONOTONIC_RAW, &end_time);
    }
    double elapsed_time = ((end_time.tv_sec - start_time.tv_sec) * 1e9 +
                              (end_time.tv_nsec - start_time.tv_nsec));
    elapsed_time = (elapsed_time)/(2*NUM_ITERATIONS);
    FILE *f = fopen("./logs/process_switch_overhead.csv", "a");
    if (f == NULL) {
        perror("Failed to open log file");
        return 1;
    }
    fprintf(f, "%.2f\n",elapsed_time);
    return elapsed_time;
}

void * dummy_thread(void* args) {
    char readbuf;
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        if (read(p1[0], &readbuf, 1) != 1) {
            perror("Child thread failed to read");
            exit(1);
        }
        if (write(p2[1], "a", 1) != 1) {
            perror("Child thread failed to write");
            exit(1);
        }
    }
    return NULL;
}

// used https://stackoverflow.com/questions/965316/how-can-unix-pipes-be-used-between-main-process-and-thread
// as guidance of writing the dummy thread
double measure_thread_switch_overhead(){
    nice(-20);
    struct timespec start_time, end_time;
    if (pipe(p1) < 0 || pipe(p2) < 0) {
        perror("Failed to create pipe");
    }
    pthread_t tid;
    char readbuf;
    pthread_create(&tid, NULL, dummy_thread, NULL);
    clock_gettime(CLOCK_MONOTONIC_RAW, &start_time);
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        // Send a signal to the child thread
        if (write(p1[1], "a", 1) != 1) {
            perror("Parent thread failed to write");
            exit(1);
        }
        // Wait for a response from the child thread
        if (read(p2[0], &readbuf, 1) != 1) {
            perror("Parent thread failed to read");
            exit(1);
        }
    }
    // Stop the timer
    clock_gettime(CLOCK_MONOTONIC_RAW, &end_time);
    pthread_join(tid, NULL);
    double elapsed_time = ((end_time.tv_sec - start_time.tv_sec) * 1e9 +
                              (end_time.tv_nsec - start_time.tv_nsec));
    elapsed_time = (elapsed_time)/(2*NUM_ITERATIONS);
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
