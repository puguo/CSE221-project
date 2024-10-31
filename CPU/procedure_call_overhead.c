#include "../utils.h"
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <math.h>
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

double calculateSD(double data[]) {
    double sum = 0.0, mean, SD = 0.0;
    int i;
    for (i = 0; i < 100; ++i) {
        sum += data[i];
    }
    mean = sum / 100;
    for (i = 0; i < 100; ++i) {
        SD += pow(data[i] - mean, 2);
    }
    return sqrt(SD / 100);
}

double calculateMean(double data[]) {
    double sum = 0.0;
    int i;
    for (i = 0; i < 100; ++i) {
        sum += data[i];
    }
    return sum/100;
}

int main() {
    FILE *f = fopen("./logs/procedure_call_overhead.csv", "w");
    if (f == NULL) {
        perror("Failed to open log file");
        return 1;
    }
    fprintf(f, "%s\n", "argument num, time(ns)");
    double f0s[100];
    double f1s[100];
    double f2s[100];
    double f3s[100];
    double f4s[100];
    double f5s[100];
    double f6s[100];
    double f7s[100];
    for(int i = 0; i < 100; i++){
        double f0 = measure_f0_overhead();
        double f1 = measure_f1_overhead();
        double f2 = measure_f2_overhead();
        double f3 = measure_f3_overhead();
        double f4 = measure_f4_overhead();
        double f5 = measure_f5_overhead();
        double f6 = measure_f6_overhead();
        double f7 = measure_f7_overhead();
        f0s[i] = f0;
        f1s[i] = f1;
        f2s[i] = f2;
        f3s[i] = f3;
        f4s[i] = f4;
        f5s[i] = f5;
        f6s[i] = f6;
        f7s[i] = f7;

    }
    
    double* results[8] = {f0s,f1s,f2s,f3s,f4s,f5s,f6s,f7s};
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 100; j++){
            fprintf(f, "%d, %.2f\n", i,results[i][j]);
        }
    }
    for(int i = 0; i < 8; i++){
        fprintf(f,"%i parameter SD: %f\n",i,calculateSD(results[i]));
        fprintf(f,"%i parameter mean: %f\n",i,calculateMean(results[i]));
        printf("%i parameter SD: %f\n",i,calculateSD(results[i]));
        printf("%i parameter mean: %f\n",i,calculateMean(results[i]));
    }
    
    fclose(f);
    return 0;
}