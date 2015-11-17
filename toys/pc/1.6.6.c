#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#define RAM_SIZE 1024
#define MAX_VAL 1000

typedef union {
    int cop[3];
    int iop;
} opic;

#define dprintf printf
//#define dprintf(...)

int main()
{
    char op1, op2, op3, c;
    int  i, iop1, iop2, iop3, n;
    int ncases, op_counter, steps = 0, ip, num_instructions;
    int reg[10] = {0};
    int ram[1024] = {0};
    opic instr;

    scanf("%d\n", &ncases);
    dprintf("there are %d cases\n", ncases);

    for (n = 1; n <= ncases; n++) {
        if (n > 1) printf("\n]");
        dprintf("case #%d\n", n);
        op_counter = 0;
        ip = 0;
        num_instructions = 0;
        instr.iop = 0;
        memset(ram, 0, RAM_SIZE);
        memset(reg, 0, 10);
        while ((c = getchar()) != '\n') {
            instr.cop[op_counter++] = c-'0';
            putchar(c);
            if (op_counter >= 3) {
                instr.cop[op_counter] = '\0';
                ram[ip] = instr.iop;
                instr.cop[0] = instr.cop[1] = instr.cop[2] = '\0';
                i = getchar(); /* strip off trailing carriage return */
                dprintf("carriage return %d op_counter %d\n", i, op_counter);
                op_counter = 0;
                ip++;
                num_instructions++;
            }
        }
        // dump ram
        for (i = 0; i < ip; i++) {
            dprintf("ram[%d]=%d\n", i, ram[i]);
        }

        steps = 0;
        dprintf("num instructions: %d\n", num_instructions);
        for (ip = 0; ; ip++) {
            instr.iop = ram[ip];
            op1 = instr.cop[0];
            op2 = instr.cop[1];
            op3 = instr.cop[2];
            iop1 = op1 - '0';
            iop2 = op2 - '0';
            iop3 = op3 - '0';
            dprintf("******    op[%d] = %c%c%c\n", ip, op1, op2, op3);
            switch (op1) {
                case '1': dprintf("halt\n"); steps++; goto done; break;
                case '2': {
                              steps++; 
                              dprintf("set reg %d to %d\n", iop2, iop3); 
                              reg[iop2] = iop3;
                              reg[iop2] %= MAX_VAL;
                              dprintf("reg[%d] = %d\n", iop2, reg[iop2]);
                              break;
                          }
                case '3': {
                              steps++; 
                              dprintf("add  %d to reg %d\n", iop3, iop2); 
                              reg[iop2] += iop3;
                              reg[iop2] %= MAX_VAL;
                              dprintf("reg[%d] = %d\n", iop2, reg[iop2]);
                              break;
                          }
                case '4': {
                              steps++; 
                              dprintf("mult reg %d by %d\n", iop2, iop3); 
                              reg[iop2] *= iop3;
                              reg[iop2] %= MAX_VAL;
                              dprintf("reg[%d] = %d\n", iop2, reg[iop2]);
                              break;
                          }
                case '5': {
                              steps++; 
                              dprintf("set reg %d to value of reg %d\n", iop2, iop3); 
                              reg[iop2] = reg[iop3];
                              reg[iop2] %= MAX_VAL;
                              dprintf("reg[%d] = %d\n", iop2, reg[iop2]);
                              break;
                          }
                case '6': {
                              steps++; 
                              dprintf("add value of reg %d to reg %d\n", iop3, iop2);
                              reg[iop2] += reg[iop3];
                              reg[iop2] %= MAX_VAL;
                              dprintf("reg[%d] = %d\n", iop2, reg[iop2]);
                              break;
                          }
                case '7': {
                              steps++; 
                              dprintf("mult reg %d by value of reg %d\n", iop2, iop3); 
                              reg[iop2] *= reg[iop3];
                              reg[iop2] %= MAX_VAL;
                              dprintf("reg[%d] = %d\n", iop2, reg[iop2]);
                              break;
                          }
                case '8': {
                              steps++; 
                              dprintf("set reg %d to RAM value at addr %d\n", iop2, iop3);
                              reg[iop2] = ram[iop3];
                              reg[iop2] %= MAX_VAL;
                              dprintf("reg[%d] = %d\n", iop2, reg[iop2]);
                              break; 
                          }
                case '9': {
                              steps++; 
                              dprintf("set RAM at addr in reg %d to value in reg %d\n", iop3, iop2); 
                              ram[iop3] = reg[iop2];
                              ram[iop3] %= MAX_VAL;
                              dprintf("ram[%d] = %d\n", iop3, ram[iop2]);
                              break;
                          }
                case '0': {
                              steps++; 
                              dprintf("goto location in reg %d unless reg %d is zero\n", iop2, iop3); 
                              if (reg[iop3] != 0) {
                                  ip = reg[iop2]-1;
                                  dprintf("reg[%d] = %d, setting ip = %d\n", iop3, reg[iop3], reg[iop2]);
                              }
                              break;
                          }
                default: dprintf("urr???\n"); break;
            }
        }
done:
        dprintf("%d steps to halt\n", steps);
        printf("%d\n", steps);
    }
    return 0;
}
