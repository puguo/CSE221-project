#include "../utils.h"
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#define NUM_ITERATIONS 10000

double measure_syscall_overhead () {
  	nice(-20);
    struct timespec start_time, end_time;
    int i = 0;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start_time);
    for (; i < NUM_ITERATIONS; i++){
        getpid();
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &end_time);
    double elapsed_time = ((end_time.tv_sec - start_time.tv_sec) * 1e9 +
                              (end_time.tv_nsec - start_time.tv_nsec));
    return elapsed_time / NUM_ITERATIONS;
}

int main() {
    check_clock_resolution(CLOCK_MONOTONIC_RAW);
    set_affinity(5);
    FILE *f = fopen("./logs/syscall_overhead.csv", "w");
    if (f == NULL) {
        perror("Failed to open log file");
        return 1;
    }
    fprintf(f, "%s\n", "iteration, time(ns)");
    for(int i = 0; i < 10; i++){
        double syscall_overhead = measure_syscall_overhead();
        fprintf(f, "%d, %.2f\n", i,syscall_overhead);
    }
    fclose(f);
    return 0;
}