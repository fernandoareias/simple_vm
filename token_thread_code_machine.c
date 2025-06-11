#include <stdio.h>
#include <stdint.h>

#define STOP 0
#define ADD 1
#define MUL 2
#define PUSH 3

int run(const unsigned char *code) {
    int stack[1000], sp = 0;
    const unsigned char *ip = code;

    static void *dispatch[] = {
        &&do_stop,
        &&do_add,
        &&do_mul,
        &&do_push
    };

    #define NEXT goto *dispatch[*ip++]

    NEXT;

do_add: {
    int b = stack[--sp];
    int a = stack[--sp];
    stack[sp++] = a + b;
    NEXT;
}

do_mul: {
    int b = stack[--sp];
    int a = stack[--sp];
    stack[sp++] = a * b;
    NEXT;
}

do_push: {
    int size = *ip++;
    int val = 0;
    while (size--) val = val * 256 + *ip++;
    stack[sp++] = val;
    NEXT;
}

do_stop:
    return stack[--sp];
}

 


int main() {
    // PUSH 2, PUSH 3, ADD, PUSH 4, MUL → (2 + 3) * 4 = 20
    unsigned char code[] = {
        PUSH, 1, 2,    // PUSH 2
        PUSH, 1, 3,    // PUSH 3
        ADD,           // ADD
        PUSH, 1, 4,    // PUSH 4
        MUL,           // MUL
        STOP
    };

    int result = run(code);
    printf("Resultado: %d\n", result);
    return 0;
}
