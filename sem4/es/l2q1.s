; Write a program to add ten 32 bit numbers available in code memory and store 
; the result in data memory. 

	AREA RESET, DATA, READONLY
	EXPORT __Vectors
__Vectors
	DCD 0x10001000 ; stack pointer value when stack is empty
	DCD Reset_Handler ; reset vector
	ALIGN
	AREA mycode, CODE, READONLY
	ENTRY
	EXPORT Reset_Handler
Reset_Handler

	LDR R0, =SRC
	MOV R2, #10
	MOV R3, #0
	
loop
	LDR R1, [R0], #4
	ADD R3, R3, R1
	SUBS R2, R2, #1
	BNE loop
	
	LDR R4, =DST
	STR R3, [R4]
		
STOP
	B STOP;
	
SRC DCD 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
	AREA mydata, DATA, READWRITE

DST DCD 0
	END