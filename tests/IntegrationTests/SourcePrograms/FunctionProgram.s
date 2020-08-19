INCLUDE Constants.s

__main PROC

    ; Multiply 5 by 7
    MOV R0, #5
    MOV R1, #7
    MOV r3, #9
    MOV R5, #5
    MOV R4, #0xBEEF
    MOV R6, #6
    MOV R7, #0xC0DE
    MOV R8, #8
    BL multiply

    BL func1

    ENDP

multiply PROC

    PUSH {R3, R4, R6-R8}
    MOV R4, #0xCODE
    MOV R7, #0xBEEF

    MOV R2, #0

Top ADD R2, R0
    SUBS R1, #1
    BNE Top
    MOV R0, R2

    POP {R3, R4, R6-R8}
    BX LR

    ENDP

func1 PROC

    PUSH {LR}

    BL func2
    POP {LR}
    BX LR

    ENDP

func2 PROC

    MOV R10, #0xCAFE
    BX LR

    ENDP