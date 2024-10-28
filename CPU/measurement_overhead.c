#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
#include "../utils.h"

#define NUM_ITERATIONS 10000

double measure_clock_gettime_overhead(FILE *log_file) {
    // set to highest priority
    nice(-20);
    struct timespec start_time, end_time, ts;
    double total_time = 0;

    for (int i = 0; i < NUM_ITERATIONS; i++) {
        // since clock_gettime() has nanosecond precision, and it's overhead is
        // smaller than 1 ns, we take 100 of them and get it's average
        clock_gettime(CLOCK_MONOTONIC_RAW, &start_time);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        clock_gettime(CLOCK_MONOTONIC_RAW, &end_time);

        // get average of 100 clock_gettime() in nanoseconds
        double elapsed_time = ((end_time.tv_sec - start_time.tv_sec) * 1e9 +
                              (end_time.tv_nsec - start_time.tv_nsec))/100;
        total_time += elapsed_time;
        fprintf(log_file, "%d, %.2f\n", i,elapsed_time);
    }
    return total_time / NUM_ITERATIONS;
}

double measure_loop_overhead (FILE *log_file) {
  	nice(-20);
    struct timespec start_time, end_time;
    double total_time = 0;
    for (int i = 0; i < NUM_ITERATIONS; i++){
        int j = 0;
        clock_gettime(CLOCK_MONOTONIC_RAW, &start_time);
        for (; j < NUM_ITERATIONS; j++);
        clock_gettime(CLOCK_MONOTONIC_RAW, &end_time);
        double elapsed_time = ((end_time.tv_sec - start_time.tv_sec) * 1e9 +
                              (end_time.tv_nsec - start_time.tv_nsec))/NUM_ITERATIONS;
        total_time += elapsed_time;
        fprintf(log_file, "%d, %.2f\n", i,elapsed_time);
    }
    return total_time / NUM_ITERATIONS;
}

void check_num_iteration_affect(){
    struct timespec start_time, end_time;
    int i = 0;
    int j = 0;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start_time);
    for(; i < 100;i++);
    clock_gettime(CLOCK_MONOTONIC_RAW, &end_time);
    double elapsed_time = ((end_time.tv_sec - start_time.tv_sec) * 1e9 +
                              (end_time.tv_nsec - start_time.tv_nsec));
    printf("Time for 100 iterations: %.2f\n", elapsed_time);

    clock_gettime(CLOCK_MONOTONIC_RAW, &start_time);
    for(; i < 10000;i++);
    clock_gettime(CLOCK_MONOTONIC_RAW, &end_time);
    elapsed_time = ((end_time.tv_sec - start_time.tv_sec) * 1e9 +
                              (end_time.tv_nsec - start_time.tv_nsec));
    printf("Time for 100 iterations: %.2f\n", elapsed_time);
}

int main() {
    check_clock_resolution(CLOCK_MONOTONIC_RAW);
    set_affinity(5);
    FILE *f1 = fopen("./logs/meaasurement_overhead.csv", "w");
    if (f1 == NULL) {
        perror("Failed to open log file 1");
        return 1;
    }
    fprintf(f1, "%s\n", "iteration, time(ns)");
    double measure_overhead = measure_clock_gettime_overhead(f1);
    printf("Average overhead of clock_gettime(): %.2f ns\n", measure_overhead);
    fclose(f1);
    
    check_num_iteration_affect();
    FILE *f2 = fopen("./logs/loop_overhead.csv", "w");
    if (f2 == NULL) {
        perror("Failed to open log file 2");
        return 1;
    }
    fprintf(f2, "%s\n", "iteration, time(ns)");
    double loop_overhead = measure_loop_overhead(f2);
    printf("Average overhead of loop: %.2f ns\n", loop_overhead);

    fclose(f2);
    return 0;
}
