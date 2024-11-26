#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define ARRAY_SIZE (1 << 24)
#define ITERATIONS 100

void finish_timing(long sum) {
    printf("Sum: %ld\n", sum);
}
// wr function ref:https://github.com/intel/lmbench/blob/master/src/bw_mem.c
// wr - 4 byte write, 128 bytes(32 ints) stride
// the cache line size is 128 Bytes, 32 INTs
void rd(int *array, size_t size) {
    int *lastone = &array[size - 1];
    long sum = 0;
    int iterations = ITERATIONS;
    while (iterations-- > 0) {
        int *p = array;
        while (p <= lastone) {
            sum += 
#define DOIT(i) p[i] = 1;
            DOIT(0) DOIT(32) DOIT(64) DOIT(96);
            p += 128; 
        }
    }
    finish_timing(sum);
}
#undef DOIT

void measure_memory_reading(int *array, size_t size) {
    FILE *f = fopen("./logs/ram_write_bandwidth_64MB_Array_2.csv", "a");
    if (f == NULL) {
        perror("Failed to open log file");
        return;
    }
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start); 
    rd(array,size);
    clock_gettime(CLOCK_MONOTONIC, &end);
    double elapsed_time = (end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec);
    long total_elements = ITERATIONS * (size / 128) * 4;
    long total_bytes = total_elements * sizeof(int);

    double bandwidth = (double)total_bytes / (elapsed_time / 1e9);

    // fprintf(f, "%.2f ns\n", elapsed_time / ITERATIONS);
    fprintf(f, "%.2f GB/s\n", bandwidth / (1 << 30));
}

int main() {
    nice(-20);
    int *array = malloc(ARRAY_SIZE * sizeof(int));
    if (!array) {
        perror("Memory allocation failed\n");
        return 1;
    }

    for (size_t i = 0; i < ARRAY_SIZE; i++) {
        array[i] = i % 100;
    }

    measure_memory_reading(array, ARRAY_SIZE);

    free(array);
    return 0;
}
