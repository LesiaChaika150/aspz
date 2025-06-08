#include <stdio.h>

void broken() {
    printf("Перед маніпуляцією зі стеком\n");

    asm("addq $8, %rsp");

    printf("Цей рядок не буде виведений\n");
}

int main() {
    broken();
    return 0;
}
