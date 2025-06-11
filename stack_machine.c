#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_CODE 100
#define MAX_STACK 100

typedef enum {
    PUSH,
    ADD,
    MULTIPLY
} OpCode;

typedef struct {
    OpCode op;
    int arg; 
} Instruction;

Instruction code[MAX_CODE];
int code_size = 0;

int stack[MAX_STACK];
int sp = 0;

void compile(const char* expr) {
    const char* p = expr;
    int num;
    Instruction instr_stack[MAX_CODE];
    int instr_top = 0;

    while (*p) {
        if (isspace(*p)) {
            p++;
        } else if (isdigit(*p)) {
            num = strtol(p, (char**)&p, 10);
            code[code_size++] = (Instruction){PUSH, num};
        } else if (*p == '*') {
            instr_stack[instr_top++] = (Instruction){MULTIPLY, 0};
            p++;
        } else if (*p == '+') {
            instr_stack[instr_top++] = (Instruction){ADD, 0};
            p++;
        } else {
            printf("Erro: caractere inválido '%c'\n", *p);
            exit(1);
        }
    }

    for (int i = 0; i < instr_top; i++) {
        code[code_size++] = instr_stack[i];
    }
}

int interpret() {
    for (int pc = 0; pc < code_size; pc++) {
        Instruction instr = code[pc];
        switch (instr.op) {
            case PUSH:
                stack[sp++] = instr.arg;
                break;
            case ADD: {
                int b = stack[--sp];
                int a = stack[--sp];
                stack[sp++] = a + b;
                break;
            }
            case MULTIPLY: {
                int b = stack[--sp];
                int a = stack[--sp];
                stack[sp++] = a * b;
                break;
            }
        }
    }
    return stack[sp - 1];
}

int main() {
    const char* input = "2 + 3 * 4"; 
    compile(input);
    int result = interpret();
    printf("Resultado: %d\n", result); 
    return 0;
}
