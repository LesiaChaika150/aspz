#include <stdio.h>

void demo() {
    printf("Це функція demo()\n");
}

int main() {
    printf("Викликаємо demo()\n");
    demo();
    printf("Повернулись у main()\n");
    return 0;
}
