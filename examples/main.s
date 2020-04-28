	INCLUDE core_cm4_constants.s		; Load Constant Definitions
	INCLUDE stm32l476xx_constants.s    

	AREA    main, CODE, READONLY
	EXPORT	__main				; make __main visible to linker
	ENTRY			
				
__main	PROC

	MOV r0, #1
	
	; Enable the clock for GPIOA, GPIOB
	
	LDR r0, =RCC_BASE
	LDR r1, [r0, #RCC_AHB2ENR]
	ORR	r1, #0x3
	STR	r1, [r0, #RCC_AHB2ENR]
	
	
	; Set GPIOB pins 2,3,6,7 as output pins
	
	LDR r0, =GPIOB_BASE
	LDR	r1, [r0, #GPIO_MODER]
	BIC r1, #0xF0
	BIC	r1, #0xF000
	ORR	r1, #0x50
	ORR	r1, #0x5000
	STR	r1, [r0, #GPIO_MODER]
	
	
	; Set GPIOA pin 0 as an input pin
	
	LDR r0, =GPIOA_BASE;
	LDR	r1, [r0, #GPIO_MODER]
	BIC	r1, #0x3;
	STR	r1, [r0, #GPIO_MODER]
	
	
	LDR	r0, =GPIOB_BASE;
	LDR	r1, =GPIOA_BASE

reset
	MOV	r5, #0x0
loop	
	
	LDR	r2, =0x99999
delay
	SUBS	r2, #1
	BNE	delay
	
	AND	r6, r5, #0xC
	LSL	r6, #4
	AND	r7, r5, #0x3
	LSL	r7, #2
	ORR r6, r7
	
	STR	r6, [r0, #GPIO_ODR]
	
	ADD	r5, #1
	CMP	r5, #0xA
	BEQ	reset
	
	LDR	r3, [r1, #GPIO_IDR]
	AND	r3, #1
	CMP	r3, #1
	BEQ	reset
	
	B loop
	
	
stop 	B 		stop     		; dead loop & program hangs here

	ENDP
					
	ALIGN			

	AREA myData, DATA, READWRITE
	ALIGN

; Replace ECE1770 with your last name
str DCB "Vander",0
	END
