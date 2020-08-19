INCLUDE Constants.s

__main PROC

    MOV R1, #0
    MOV R2, #0

Top

    ADD R2, #2
    ADD R1, #1
    CMP R1, #10
    BNE Top

    MOV R0, #0
    ADDS R2, R0
    BEQ Label2

Label1

    ORR R3, R0, #0xFF

    CMP R3, R0
    MOV R4, #0
    ADDGE R4, #5
    ADDLE R4, #5
    ADDGT R4, #5
    ADDLT R4, #5

    BICGTS R4, #0x03

    BPL Label3
    MOV R4, #0xBEEF

Label3

    MOV R6, #0
    MOVS R5, #-2
    ORRMI R6, #0xAA
    ADDNV R6, #100
    
Label2

    MOV R12, #4

    ENDP