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

// Accumulate the contents of the memory region pointed to by buf through different steps.
//Ref: https://github.com/intel/lmbench/blob/master/src/lib_timing.c#L1581
long
bread(void* buf, long nbytes)
{
	long sum = 0;
	register long *p, *next;
	register char *end;

	p = (long*)buf;
	end = (char*)buf + nbytes;
	for (next = p + 128; (void*)next <= (void*)end; p = next, next += 128) {
		sum +=
			p[0]+p[1]+p[2]+p[3]+p[4]+p[5]+p[6]+p[7]+
			p[8]+p[9]+p[10]+p[11]+p[12]+p[13]+p[14]+
			p[15]+p[16]+p[17]+p[18]+p[19]+p[20]+p[21]+
			p[22]+p[23]+p[24]+p[25]+p[26]+p[27]+p[28]+
			p[29]+p[30]+p[31]+p[32]+p[33]+p[34]+p[35]+
			p[36]+p[37]+p[38]+p[39]+p[40]+p[41]+p[42]+
			p[43]+p[44]+p[45]+p[46]+p[47]+p[48]+p[49]+
			p[50]+p[51]+p[52]+p[53]+p[54]+p[55]+p[56]+
			p[57]+p[58]+p[59]+p[60]+p[61]+p[62]+p[63]+
			p[64]+p[65]+p[66]+p[67]+p[68]+p[69]+p[70]+
			p[71]+p[72]+p[73]+p[74]+p[75]+p[76]+p[77]+
			p[78]+p[79]+p[80]+p[81]+p[82]+p[83]+p[84]+
			p[85]+p[86]+p[87]+p[88]+p[89]+p[90]+p[91]+
			p[92]+p[93]+p[94]+p[95]+p[96]+p[97]+p[98]+
			p[99]+p[100]+p[101]+p[102]+p[103]+p[104]+
			p[105]+p[106]+p[107]+p[108]+p[109]+p[110]+
			p[111]+p[112]+p[113]+p[114]+p[115]+p[116]+
			p[117]+p[118]+p[119]+p[120]+p[121]+p[122]+
			p[123]+p[124]+p[125]+p[126]+p[127];
	}
	for (next = p + 16; (void*)next <= (void*)end; p = next, next += 16) {
		sum +=
			p[0]+p[1]+p[2]+p[3]+p[4]+p[5]+p[6]+p[7]+
			p[8]+p[9]+p[10]+p[11]+p[12]+p[13]+p[14]+
			p[15];
	}
	for (next = p + 1; (void*)next <= (void*)end; p = next, next++) {
		sum += *p;
	}
	return sum;
}