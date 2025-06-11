#include <stdio.h>
#include <stdlib.h>

int main() {
    int xa = 1000000;
    int xb = 1000000;
    int num = xa * xb;

    printf("Результат множення: %d\n", num);

    // Перевірка на переповнення
    if (xa != 0 && num / xa != xb) {
        printf("Виявлено переповнення під час множення!\n");
        return 1;
    }

    void *ptr = malloc(num);

    if (ptr == NULL) {
        printf("malloc повернув NULL (ймовірно через переповнення або надто великий розмір)\n");
    } else {
        printf("malloc успішно виділив пам'ять\n");
        free(ptr);
    }

    return 0;
}