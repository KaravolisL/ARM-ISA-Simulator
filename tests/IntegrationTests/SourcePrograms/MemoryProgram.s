INCLUDE Constants.s

__main PROC

    LDR r3, =array
    LDR r0, [r3]
    
    LDR r1, [R3, #4]

    LDR R2, [R3, #8]!

    LDR r4, =myArray
    LDR r5, =size
    LDRB r5, [r5]
    MOV r6, #0

top
    LDRB r7, [r4], #1
    ADD r6, r7
    CMP r5, #0
    BEQ end
    SUB r5, #1
    B top
end

    ;MOV R4, R6

    LDR r7, =myInt
    LDRSB r7, [r7]

    ENDP

array DCD 25, 26, 27
myArray DCB 0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20

    ALIGN

size DCB 11
    ALIGN
myInt DCB -5