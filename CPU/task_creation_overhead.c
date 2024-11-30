#include "../utils.h"
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <pthread.h>
#include <sys/wait.h>
#include <stdlib.h> 
#define NUM_ITERATIONS 10000

// Process create is followed by a set of neccesary comparsion, we are not sure about the
// affect of that, but putting measurement inside might be affected by granularity, so 
// we test both
void measure_process_create_overhead_outside (int index) {
  	nice(-20);
    struct timespec start_time, end_time;
    int i = 0;
    pid_t pid;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start_time);
    for (; i < NUM_ITERATIONS; i++){
        pid = fork();
        if(pid == -1){
            perror("fork");
            exit(1);
        } else if (pid == 0){
            exit(0);
        } else {
            if (waitpid(pid, NULL, 0) == -1) {
                exit(1);
            }
        }
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &end_time);
    double elapsed_time = ((end_time.tv_sec - start_time.tv_sec) * 1e9 +
                              (end_time.tv_nsec - start_time.tv_nsec))/NUM_ITERATIONS;
    FILE *f = fopen("./logs/process_create_overhead.csv", "a");
    if (f == NULL) {
        perror("Failed to open log file");
    }
    fprintf(f, "%d, %.2f, outside\n", index,elapsed_time);
    fclose(f);
}

void measure_process_create_overhead_inside (int index) {
  	nice(-20);
    struct timespec start_time, end_time;
    double total_time = 0;
    int i = 0;
    pid_t pid;
    for (; i < NUM_ITERATIONS; i++){
        clock_gettime(CLOCK_MONOTONIC_RAW, &start_time);
        pid = fork();
        if(pid > 0){
            clock_gettime(CLOCK_MONOTONIC_RAW, &end_time);
            double elapsed_time = ((end_time.tv_sec - start_time.tv_sec) * 1e9 +
                              (end_time.tv_nsec - start_time.tv_nsec));
            total_time += elapsed_time;
            wait(NULL);
        } else if (pid == -1){
            perror("fork");
            exit(1);
        } else{
            exit(0);
        }
    }
    FILE *f = fopen("./logs/process_create_overhead.csv", "a");
    if (f == NULL) {
        perror("Failed to open log file");
    }
    fprintf(f, "%d, %.2f, inside\n", index,total_time/ NUM_ITERATIONS);
    fclose(f);
}


typedef struct {
    struct timespec start_time;
    struct timespec end_time;
} thread_data_t;

void* thread_dummy(void *arg) {
    thread_data_t *data = (thread_data_t *)arg;

    // Record the thread end time
    clock_gettime(CLOCK_MONOTONIC_RAW, &data->end_time);

    pthread_exit(0);
}

void measure_thread_create_overhead(int index) {
    nice(-20); 
    pthread_t tid;
    thread_data_t thread_data;
    double total_time = 0.0;
    int i;

    FILE *f = fopen("./logs/thread_create_overhead.csv", "a");
    if (f == NULL) {
        perror("Failed to open log file");
        return;
    }

    for (i = 0; i < NUM_ITERATIONS; i++) {
        clock_gettime(CLOCK_MONOTONIC_RAW, &thread_data.start_time);
        if (pthread_create(&tid, NULL, thread_dummy, &thread_data) != 0) {
            perror("Error: pthread_create failed");
            fclose(f);
            return;
        }
        if (pthread_join(tid, NULL) != 0) {
            perror("Error: pthread_join failed");
            fclose(f);
            return;
        }

        double elapsed_time = ((thread_data.end_time.tv_sec - thread_data.start_time.tv_sec) * 1e9 +
                               (thread_data.end_time.tv_nsec - thread_data.start_time.tv_nsec));
        total_time += elapsed_time;
        fprintf(f, "%d, %.2f\n", i, elapsed_time);
    }

    // Log the average time for all iterations
    fprintf(f, "Average, %.2f\n", total_time / NUM_ITERATIONS);
    fclose(f);
}



int main() {
    FILE *f = fopen("./logs/process_create_overhead.csv", "w");
    if (f == NULL) {
        perror("Failed to open log file");
        return 1;
    }
    fprintf(f, "%s\n", "iteration, time(ns), inside/outside");
    fclose(f);
    for(int i = 0; i < 10; i++){
        measure_process_create_overhead_outside(i);
    }
    for(int i = 0; i < 10; i++){
        measure_process_create_overhead_inside(i);
    }
     for(int i = 0; i < 10; i++){
        measure_thread_create_overhead(i);
    }
    return 0;
}