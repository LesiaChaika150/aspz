#include <stdio.h>



void damage_stack() {

    printf("Перед зміщенням стека\n");

    asm("addq $8, %rsp"); 

}



int main() {

    damage_stack();

    printf("Цей рядок не буде виведено\n");

    return 0;

}

