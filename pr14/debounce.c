#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>

timer_t debounce_timer;
volatile sig_atomic_t debounce_triggered = 0;

void debounce_handler(int sig, siginfo_t *si, void *uc) {
    (void)sig; (void)si; (void)uc;
    debounce_triggered = 1;
}

void set_noncanonical_mode(int enable) {
    static struct termios oldt, newt;

    if (enable) {
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    } else {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    }
}

void arm_debounce_timer() {
    struct itimerspec its;
    its.it_value.tv_sec = 0;
    its.it_value.tv_nsec = 500 * 1000000; // 500 мс
    its.it_interval.tv_sec = 0;
    its.it_interval.tv_nsec = 0;
    timer_settime(debounce_timer, 0, &its, NULL);
}

int main() {
    struct sigaction sa = {0};
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = debounce_handler;
    sigaction(SIGRTMIN, &sa, NULL);

    struct sigevent sev = {0};
    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = SIGRTMIN;
    timer_create(CLOCK_REALTIME, &sev, &debounce_timer);

    printf("Натисніть клавіші (натисніть 'q' щоб вийти)...\n");

    set_noncanonical_mode(1);

    char c;
    while (1) {
        if (read(STDIN_FILENO, &c, 1) > 0) {
            if (c == 'q') break;
            printf("[!] Натиснуто клавішу: %c\n", c);
            arm_debounce_timer();
        }

        if (debounce_triggered) {
            debounce_triggered = 0;
            printf("Debounced дія: користувач зупинився\n");
        }

        usleep(10000); // невелика затримка для CPU
    }

    set_noncanonical_mode(0);
    timer_delete(debounce_timer);
    printf("Програма завершена.\n");
    return 0;
}
