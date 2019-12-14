; Feature demo

primes  DCD 1,2,3,5,7
        LDR R0, =primes
        LDR R1, [R0]
        ;
        ;
        LDR R0, =0xBEEF
        LSL R1, R0, #4
        LSR R2, R0, #8
        ASR R3, R0, #15
        ROR R4, R0, #16
        RRX R5, R0

        END

