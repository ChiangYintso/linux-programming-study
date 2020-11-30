#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <setjmp.h>

jmp_buf excep;

static void sigfpe_handler(int sig) {
    puts("SIGFE exception!!!!");
    longjmp(excep, 1);
}

_Noreturn void *calc(void *args) {
    for (;;) {
        setjmp(excep);

        for (int i = 3; i > -3; --i) {
            printf("%d\n", 30 / i);
            sleep(1);
        }
    }
}

int main() {
    // uncomment this to see signal handler's usage
//    signal(SIGFPE, sigfpe_handler);
    pthread_t tid;
    pthread_create(&tid, NULL, calc, NULL);
    for (;;) {
        puts("go on");
        sleep(1);
    }
}