#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
#include <mach/mach.h>
#include <mach/thread_policy.h>
#include <pthread.h>


void check_clock_resolution(clockid_t clock) {
    struct timespec ts;
    clock_getres(clock, &ts);
    printf("Clock resolution: %ld sec, %ld nsec\n", ts.tv_sec, ts.tv_nsec);
}

// Modified based on this
// https://stackoverflow.com/questions/77422201/is-it-still-possible-to-set-thread-affinity-in-macos
// https://forums.developer.apple.com/forums/thread/703361
// But doesn't seem to be supported as described in many posts
void set_affinity(int cpu_id) {
    thread_affinity_policy_data_t policy;;
    policy.affinity_tag = cpu_id;
    kern_return_t t1 = thread_policy_set(pthread_mach_thread_np(pthread_self()),
                                         THREAD_AFFINITY_POLICY,
                                         (thread_policy_t)&policy,
                                         THREAD_AFFINITY_POLICY_COUNT);

    if (t1 == KERN_SUCCESS) {
        printf("set cores success");
    } else {
        printf("fail set : %d\n", t1);
    }
}