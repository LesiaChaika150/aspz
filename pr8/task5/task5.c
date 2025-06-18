#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    char *data = malloc(100);
    if (!data) {
        perror("malloc");
        return 1;
    }

    strcpy(data, "Оригінальні дані");

    printf("До fork(): %s\n", data);

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        printf("Дочірній процес: data = %s\n", data);
        strcpy(data, "Змінено в дочірньому");
        printf("Дочірній процес (після зміни): data = %s\n", data);
    } else {
        sleep(1); 
        printf("Батьківський процес: data = %s\n", data);
        strcpy(data, "Змінено в батьківському");
        printf("Батьківський процес (після зміни): data = %s\n", data);
    }

    free(data);
    return 0;
}
