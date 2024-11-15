#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define ARRAY_SIZE (1 << 24)
#define ITERATIONS 100

void finish_timing(long sum) {
    printf("Sum: %ld\n", sum);
}
// rd function ref:https://github.com/intel/lmbench/blob/master/src/bw_mem.c
// rd - 4 byte read, 16 byte stride
void rd(int *array, size_t size) {
    int *lastone = &array[size - 1];
    long sum = 0;
    int iterations = ITERATIONS;
    while (iterations-- > 0) {
        int *p = array;
        while (p <= lastone) {
            sum += 
#define DOIT(i) p[i] +
            DOIT(0) DOIT(4) DOIT(8) DOIT(12) DOIT(16) DOIT(20) DOIT(24)
            DOIT(28) DOIT(32) DOIT(36) DOIT(40) DOIT(44) DOIT(48) DOIT(52)
            DOIT(56) DOIT(60) DOIT(64) DOIT(68) DOIT(72) DOIT(76)
            DOIT(80) DOIT(84) DOIT(88) DOIT(92) DOIT(96) DOIT(100)
            DOIT(104) DOIT(108) DOIT(112) DOIT(116) DOIT(120)
            p[124];
            p += 128; 
        }
    }
    finish_timing(sum);
}
#undef DOIT

void measure_memory_reading(int *array, size_t size) {
    FILE *f = fopen("./logs/ram_read_bandwidth_64MB_Array.csv", "a");
    if (f == NULL) {
        perror("Failed to open log file");
        return 1;
    }
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start); 
    rd(array,size);
    clock_gettime(CLOCK_MONOTONIC, &end);
    double elapsed_time = (end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec);
    long total_elements = ITERATIONS * (size / 128) * 32;
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
