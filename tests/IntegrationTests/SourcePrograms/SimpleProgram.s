INCLUDE Constants.s

__main PROC

    MOV R1, #0xAA

    ADD R2, R1, #0xA ; R2 = 0xB4

    MOV R3, #0x66
    AND R3, R1 ; R3 = 0x22

    BIC R4, R1, #0x0F ; R4 = 0xA0

    NOP

    MOV R0, #0x50
    EOR R5, R1, R0 ; R5 = 0xFA

    MOV R0, #65
    ORR R6, R1, R0 ; R6 = 0xEB

    NOP

    B MyLabel

    MOV R7, #0xBEEF

MyLabel MOV R0, #0xFF
    MOV R7, #7 ; R7 = 7

    ENDP