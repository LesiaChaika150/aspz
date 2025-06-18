#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <sys/signalfd.h>
#include <string.h>
#include <errno.h>

#define NUM_SIGNALS 3

void* signal_listener(void* arg) {
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);

    int sfd = signalfd(-1, &mask, 0);
    if (sfd == -1) {
        perror("signalfd");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < NUM_SIGNALS; i++) {
        struct signalfd_siginfo fdsi;
        ssize_t s = read(sfd, &fdsi, sizeof(fdsi));
        if (s != sizeof(fdsi)) {
            perror("read");
            exit(EXIT_FAILURE);
        }

        printf("[Listener] Отримано сигнал %d від PID %d\n", fdsi.ssi_signo, fdsi.ssi_pid);
    }

    close(sfd);
    return NULL;
}

int main() {
    // Блокуємо сигнал SIGUSR1 в усій програмі
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);
    if (pthread_sigmask(SIG_BLOCK, &mask, NULL) != 0) {
        perror("pthread_sigmask");
        exit(EXIT_FAILURE);
    }

    // Створюємо потік-слухача
    pthread_t listener;
    pthread_create(&listener, NULL, signal_listener, NULL);

    sleep(1);  // даємо потоку активуватись

    // Надсилаємо 3 сигнали
    for (int i = 0; i < NUM_SIGNALS; i++) {
        kill(getpid(), SIGUSR1);
        usleep(100000); // невелика пауза
    }

    // Чекаємо завершення потоку
    pthread_join(listener, NULL);
    printf("Обробку завершено. Програма завершена.\n");
    return 0;
}
