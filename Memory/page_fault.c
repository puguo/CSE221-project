#include <stdio.h>
#include "../utils.h"
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/resource.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#define	CHK(x)	if ((long)(x) == -1) { perror("x"); exit(1); }
#define FILENAME "./file/1g_file"
#define FILE_SIZE (1 * 1024 * 1024 * 1024)  // 1 GB file, generated through command 'dd if=/dev/zero of=1g_file bs=1G count=1'

/*
 * We are not using this version for page fault measurement because bread is causing 
 * minor page fault(occurs when a process accesses a memory page that is not currently mapped 
 * in the process’s virtual memory address space but is already in physical memory).
 * 
 * Instead we are hoping only major page fault(page not in RAM and required to load from disk) exists for better measurement.
 */

// void measure_page_fault_version_1(const char *filename, size_t nbytes) {
//     struct timespec start, end;
//     int fd;
//     void *p;
//     struct rusage usage;
//     CHK(fd = open(filename, O_RDONLY));
//     CHK(p = mmap(0, nbytes, PROT_READ, MAP_SHARED, fd, 0));
//     clock_gettime(CLOCK_MONOTONIC, &start); 
//     bread(p, nbytes);
//     clock_gettime(CLOCK_MONOTONIC, &end); 
//     CHK(getrusage(RUSAGE_SELF, &usage));
//     close(fd);
//     munmap(p, nbytes);
//     double elapsed_time = (end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec);
//     printf("Time taken: %lf ns\n", elapsed_time);
//     double elapsed_time_in_s = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
//     printf("Time taken: %lf s\n", elapsed_time_in_s);
//     printf("Major Page faults: %ld\n", usage.ru_majflt);
//     printf("Minor Page faults: %ld\n", usage.ru_minflt);
//     printf("Total Page faults: %ld\n", usage.ru_majflt + usage.ru_minflt);
// }

// Ref: https://linux.die.net/man/2/getrusage
// Ref: https://github.com/intel/lmbench/blob/master/src/bw_mmap_rd.c

double measure_page_fault(const char *filename, size_t nbytes) {
    struct timespec start, end;
    int fd;
    void *p;
    struct rusage usage_before, usage_after;

    CHK(fd = open(filename, O_RDONLY));
    CHK(p = mmap(0, nbytes, PROT_READ, MAP_SHARED, fd, 0));
    
    CHK(getrusage(RUSAGE_SELF, &usage_before));
    // printf("Major Page faults before: %ld\n", usage_before.ru_majflt);
    // printf("Minor Page faults before: %ld\n", usage_before.ru_minflt);
    size_t page_size = sysconf(_SC_PAGESIZE);
    size_t num_pages = nbytes / page_size;

    printf("Page size: %zu bytes\n", page_size);
    printf("Total pages to access: %zu\n", num_pages);

    clock_gettime(CLOCK_MONOTONIC, &start);
    for (size_t i = 0; i < num_pages; i++) {
        // access by each page to ganrantee a page fault
        volatile char access = *((char *)p + i * page_size); 
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    CHK(getrusage(RUSAGE_SELF, &usage_after));
    double total_elapsed_time_ns = (end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec);
    double total_elapsed_time_s = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    long major_faults = usage_after.ru_majflt - usage_before.ru_majflt;
    long minor_faults = usage_after.ru_minflt - usage_before.ru_minflt;

    double avg_time_per_fault_ns = total_elapsed_time_ns / (major_faults + minor_faults);
    if (minor_faults == 0) {
        printf("Total Time taken: %lf ns (%lf s)\n", total_elapsed_time_ns, total_elapsed_time_s);
        printf("Major Page faults: %ld\n", major_faults);
        printf("Minor Page faults: %ld\n", minor_faults);
        printf("Average time per page fault: %lf ns\n", avg_time_per_fault_ns);
        close(fd);
        munmap(p, nbytes);
        return avg_time_per_fault_ns;
    } else {
        printf("Skipping logging since minor page faults were non-zero\n");
    }
    close(fd);
    munmap(p, nbytes);
    return -1;
}
int main(int argc, char **argv) {
    nice(-20);
    FILE *f = fopen("./logs/page_fault.csv", "a");
    if (f == NULL) {
        perror("Failed to open log file");
        return 1;
    }
    double res = measure_page_fault(FILENAME, FILE_SIZE);
    if(res != -1){
        fprintf(f,"%lf \n", res);
    }
    return 0;
}
