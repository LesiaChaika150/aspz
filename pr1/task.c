#include <stdio.h>
#include <stdint.h>

// Функція для виводу числа у двійковому вигляді
void print_binary(uint8_t val) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", (val >> i) & 1);
    }
}

// Інверсія бітів у діапазоні [from_bit, to_bit]
uint8_t invert_bits(uint8_t x, int from_bit, int to_bit) {
    uint8_t mask = 0;

    for (int i = from_bit; i <= to_bit; i++) {
        mask |= (1 << i);
    }

    return x ^ mask;
}

int main() {
    uint8_t x, y;
    int from, to;

    printf("Введіть значення x (0-255): ");
    scanf("%hhu", &x);

    printf("Введіть діапазон бітів для інверсії (від 0 до 7):\n");
    printf("Початковий біт (від): ");
    scanf("%d", &from);
    printf("Кінцевий біт (до): ");
    scanf("%d", &to);

    y = invert_bits(x, from, to);

    printf("Оригінал: ");
    print_binary(x);
    printf(" (%u)\n", x);

    printf("Інвертовано: ");
    print_binary(y);
    printf(" (%u)\n", y);

    return 0;
}
