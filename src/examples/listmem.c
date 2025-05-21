#include "user/syscall.h"
#include "stdio.h"
//#include "syscall-nr.h"
void sleep(int ticks) {
    int i, j;
    for (i = 0; i < ticks * 1000000; i++) {
        j = i * i;
    }
}

int main(void) {
    int i;
    for (i = 0; i < 10; i++) {
        mem_usage();
        sleep(2);  // sleep bận ~2 giây
    }
    return 0;
}
