#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <math.h>
#include <unistd.h>

#define ITERATIONS 1000000

void measure_latency(int *array, size_t size, double *latency, int stride) {
    struct timespec start, end;
    int cur = 0;
    int last = 0;
    int n_stride = stride/4;
    // Initialize the array to simulate a curricular linked list with a certain stride(to simulate random memory access)
    for (int i = 0; i < size; i += n_stride) {
        array[i] = (i+n_stride) % size;
        // printf("%d ", array[i]);
        last = i;
    }
    array[last] = 0;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    for (size_t i = 0; i < ITERATIONS; ++i) {
        cur  = array[cur];
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    double elapsed_time = ((end.tv_sec - start.tv_sec) * 1e9 +
                              (end.tv_nsec - start.tv_nsec));
    *latency = elapsed_time / ITERATIONS; 
}
// Use ’gcc -O0 -o ram_latency ram_latency.c‘ to avoid compiler optimization
int main() {
    nice(-20);
    size_t max_size = 1 << 30; // 4GB array
    size_t min_size = 1 << 10 ; // 4KB array

    printf("Log(Size), Latency(ns)\n");
    FILE *f = fopen("./logs/latency_results_2.csv", "a");
    if (f == NULL) {
        perror("Failed to open log file");
        return 1;
    }
    for (size_t size = min_size; size <= max_size; size <<= 1) {
        int *array = malloc(size * sizeof(int));
        if (!array) {
            perror("Memory allocation failed\n");
            return 1;
        }
        for (size_t i = 0; i < size; ++i) {
            array[i] = i;
        }
        // The cache line size is 128 Bytes, to avoid cache prefetch, the stride would start from 1<<7 bytes.
        for (int stride = 1<<7; stride <= 1<<20; stride <<= 1) {
            double latency;
            measure_latency(array, size, &latency, stride);
            printf("%f, %.2f\n", log2(size * sizeof(int)), latency);
            fprintf(f, "%f, %d, %.2f\n", log2(size * sizeof(int)), stride, latency);
        }
        fprintf(f, "\n");

        free(array); 
    }

    return 0;
}