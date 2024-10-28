#include "../utils.h"
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#define NUM_ITERATIONS 10000

void f0() {}
void f1(int n1) {}
void f2(int n1, int n2) {}
void f3(int n1, int n2, int n3) {}
void f4(int n1, int n2, int n3, int n4) {}
void f5(int n1, int n2, int n3, int n4, int n5) {}
void f6(int n1, int n2, int n3, int n4, int n5, int n6) {}
void f7(int n1, int n2, int n3, int n4, int n5, int n6, int n7) {}

double measure_f0_overhead () {
  	nice(-20);
    struct timespec start_time, end_time;
    int i = 0;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start_time);
    for (; i < NUM_ITERATIONS; i++){
        f0();
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &end_time);
    double elapsed_time = ((end_time.tv_sec - start_time.tv_sec) * 1e9 +
                              (end_time.tv_nsec - start_time.tv_nsec));
    return elapsed_time / NUM_ITERATIONS;
}

double measure_f1_overhead () {
  	nice(-20);
    struct timespec start_time, end_time;
    int i = 0;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start_time);
    for (; i < NUM_ITERATIONS; i++){
        f1(0);
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &end_time);
    double elapsed_time = ((end_time.tv_sec - start_time.tv_sec) * 1e9 +
                              (end_time.tv_nsec - start_time.tv_nsec));
    return elapsed_time / NUM_ITERATIONS;
}

double measure_f2_overhead () {
  	nice(-20);
    struct timespec start_time, end_time;
    int i = 0;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start_time);
    for (; i < NUM_ITERATIONS; i++){
        f2(0,0);
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &end_time);
    double elapsed_time = ((end_time.tv_sec - start_time.tv_sec) * 1e9 +
                              (end_time.tv_nsec - start_time.tv_nsec));
    return elapsed_time / NUM_ITERATIONS;
}

double measure_f3_overhead () {
  	nice(-20);
    struct timespec start_time, end_time;
    int i = 0;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start_time);
    for (; i < NUM_ITERATIONS; i++){
        f3(0,0,0);

    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &end_time);
    double elapsed_time = ((end_time.tv_sec - start_time.tv_sec) * 1e9 +
                              (end_time.tv_nsec - start_time.tv_nsec));
    return elapsed_time / NUM_ITERATIONS;
}

double measure_f4_overhead () {
  	nice(-20);
    struct timespec start_time, end_time;
    int i = 0;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start_time);
    for (; i < NUM_ITERATIONS; i++){
        f4(0,0,0,0);
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &end_time);
    double elapsed_time = ((end_time.tv_sec - start_time.tv_sec) * 1e9 +
                              (end_time.tv_nsec - start_time.tv_nsec));
    return elapsed_time / NUM_ITERATIONS;
}

double measure_f5_overhead () {
  	nice(-20);
    struct timespec start_time, end_time;
    int i = 0;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start_time);
    for (; i < NUM_ITERATIONS; i++){
        f5(0,0,0,0,0);
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &end_time);
    double elapsed_time = ((end_time.tv_sec - start_time.tv_sec) * 1e9 +
                              (end_time.tv_nsec - start_time.tv_nsec));
    return elapsed_time / NUM_ITERATIONS;
}

double measure_f6_overhead () {
  	nice(-20);
    struct timespec start_time, end_time;
    int i = 0;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start_time);
    for (; i < NUM_ITERATIONS; i++){
        f6(0,0,0,0,0,0);
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &end_time);
    double elapsed_time = ((end_time.tv_sec - start_time.tv_sec) * 1e9 +
                              (end_time.tv_nsec - start_time.tv_nsec));
    return elapsed_time / NUM_ITERATIONS;
}

double measure_f7_overhead () {
  	nice(-20);
    struct timespec start_time, end_time;
    int i = 0;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start_time);
    for (; i < NUM_ITERATIONS; i++){
        f7(0,0,0,0,0,0,0);
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &end_time);
    double elapsed_time = ((end_time.tv_sec - start_time.tv_sec) * 1e9 +
                              (end_time.tv_nsec - start_time.tv_nsec));
    return elapsed_time / NUM_ITERATIONS;
}

int main() {
    FILE *f = fopen("./logs/procedure_call_overhead.csv", "w");
    if (f == NULL) {
        perror("Failed to open log file");
        return 1;
    }
    fprintf(f, "%s\n", "argument num, time(ns)");
    double f0 = measure_f0_overhead();
    double f1 = measure_f1_overhead();
    double f2 = measure_f2_overhead();
    double f3 = measure_f3_overhead();
    double f4 = measure_f4_overhead();
    double f5 = measure_f5_overhead();
    double f6 = measure_f6_overhead();
    double f7 = measure_f7_overhead();
    double results[8] = {f0,f1,f2,f3,f4,f5,f6,f7};
    for(int i = 0; i < 8; i++){
        fprintf(f, "%d, %.2f\n", i,results[i]);
    }
    fclose(f);
    return 0;
}