#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#define RAM_SIZE 1024
#define MAX_VAL 1000
#define dprintf printf
//#define dprintf(...)

struct istr {
    union {
        char op[3];
        int iop;
    };
};

int main()
{
    int  c, exit, iop1, iop2, iop3, i, instruct, d, n, a, s;
    int ncases, steps, IP;
    struct istr ram[1024];
    struct istr reg[10];
    char instr[5];

    scanf("%d", &ncases);
    fgets(instr, sizeof(instr), stdin);
    fgets(instr, sizeof(instr), stdin);

    dprintf("there are %d cases\n", ncases);

    for (i = 1; i <= ncases; i++) {
        if (i > 1) {
            printf("\n");
        }
        dprintf("case #%d\n", i);
        memset(ram, 0, 1024 * sizeof(struct istr));
        memset(reg, 0, 10 * sizeof(struct istr));
        IP = 0;
        while (fgets(instr, sizeof(instr), stdin)) {
            if (instr[0] == '\n') break;
            ram[IP].op[0] = instr[0];
            ram[IP].op[1] = instr[1];
            ram[IP].op[2] = instr[2];
            dprintf("ram[%d]={%c%c%c}\n", IP, ram[IP].op[0], ram[IP].op[1], ram[IP].op[2]);
            IP++;
        }
        continue;
        steps = exit = IP = 0;
        while (!exit) {
            int v3 = ram[IP].op[2] - '0'; int v2 = ram[IP].op[1] - '0'; int v1 = ram[IP].op[0] - '0';
            iop1 = v1 % 10; iop2 = v2 % 10; iop3 = v3 % 10;
            dprintf("ram[%03d]=> [%d,%d,%d]\n", IP, iop1, iop2, iop3);
            switch (iop1) {
                case 1: 
                    dprintf("halt\n"); 
                    steps++; IP++; 
                    exit = 1; 
                    break;
                case 2:
                    steps++; IP++; 
                    d = iop2; n = iop3;
                    dprintf("set reg %d to %d\n", d, n); 
                    reg[d].iop = n;
                    reg[d].iop %= MAX_VAL;
                    dprintf("reg[%d] = %d\n", d, reg[d].iop);
                    break;
                case 3:
                    steps++; IP++; 
                    d = iop2; n = iop3;
                    dprintf("add  %d to reg %d\n", n, d); 
                    reg[d].iop += n;
                    reg[d].iop %= MAX_VAL;
                    dprintf("reg[%d] = %d\n", d, reg[d].iop);
                    break;
                case 4:
                    steps++; IP++; 
                    d = iop2; n = iop3;
                    dprintf("mult reg %d by %d\n", d, n); 
                    reg[d].iop *= n;
                    reg[d].iop %= MAX_VAL;
                    dprintf("reg[%d] = %d\n", d, reg[d].iop);
                    break;
                case 5:
                    steps++; IP++; 
                    d = iop2; s = iop3;
                    dprintf("set reg %d to value of reg %d\n", d, s); 
                    reg[d].iop = reg[s].iop;
                    reg[d].iop %= MAX_VAL;
                    dprintf("reg[%d] = %d\n", d, reg[d].iop);
                    break;
                case 6:
                    steps++; IP++; 
                    d = iop2; s = iop3;
                    dprintf("add value of reg %d to reg %d\n", s, d);
                    reg[d].iop += reg[s].iop;
                    reg[d].iop %= MAX_VAL;
                    dprintf("reg[%d] = %d\n", d, reg[d].iop);
                    break;
                case 7:
                    steps++; IP++; 
                    d = iop2; s = iop3;
                    dprintf("mult reg %d by value of reg %d\n", d, s); 
                    reg[d].iop *= reg[s].iop;
                    reg[d].iop %= MAX_VAL;
                    dprintf("reg[%d] = %d\n", d, reg[d].iop);
                    break;
                case 8:
                    steps++; IP++; 
                    d = iop2; a = iop3;
                    dprintf("set reg %d to RAM value at addr %d\n", d, a);
                    reg[d].iop = ram[reg[a].iop].iop;
                    reg[d].iop %= MAX_VAL;
                    dprintf("reg[%d] = %d\n", d, reg[d].iop);
                    break; 
                case 9:
                    steps++; IP++; 
                    s = iop2; a = iop3;
                    dprintf("set the valume in RAM at addr in reg %d to value in reg %d\n", a, s); 
                    ram[reg[a].iop].iop = reg[s].iop;
                    ram[a].iop %= MAX_VAL;
                    dprintf("ram[%d] = %d\n", a, ram[a].iop);
                    break;
                case 0:
                    steps++; IP++; 
                    d = iop2; s = iop3;
                    dprintf("goto location in reg %d unless reg %d is zero\n", d, s); 
                    if (reg[s].iop != 0) {
                        IP = reg[d].iop;
                        dprintf("reg[%d] = %d, setting IP = %d\n", d, reg[d].iop, IP);
                    }
                    break;
                default: 
                    dprintf("urr???\n"); 
                    break;
            }
        }
        printf("%d\n", steps);
    }
    return 0;
}
