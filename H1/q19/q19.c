#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
static inline uint64_t read_tsc() {
    uint32_t low, high;
    __asm__ __volatile__ (
        "rdtsc" 
        : "=a" (low), "=d" (high)
    );
    return ((uint64_t)high << 32) | low;
}

int main() {
    uint64_t start = read_tsc();
    pid_t pid = getpid();
    uint64_t end = read_tsc();
    uint64_t elapsed = end - start;
    printf("PID: %d\n", pid);
    printf("Time taken: %lu TSC ticks\n", elapsed);

    return 0;
}

