#include <stdio.h>
#include <stdint.h>

#define STOP 0
#define ADD 1
#define MUL 2
#define PUSH 3

#define pop() (stack[--sp])
#define push(X) (stack[sp++] = (X))

int run(const unsigned char *code) {
    int stack[1000];
    int sp = 0;
    const unsigned char *ip = code;

    while (*ip != STOP) {
        switch (*ip++) {
            case ADD: {
                int b = pop();
                int a = pop();
                push(a + b);
                break;
            }
            case MUL: {
                int b = pop();
                int a = pop();
                push(a * b);
                break;
            }
            case PUSH: {
                int size = *ip++;
                int val = 0;
                while (size--) {
                    val = val * 256 + *ip++;
                }
                push(val);
                break;
            }
            default:
                printf("Erro: instrução inválida: %d\n", *(ip - 1));
                return -1;
        }
    }
    return pop();
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
