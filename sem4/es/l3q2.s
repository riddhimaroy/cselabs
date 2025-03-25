;2. Find the sum of ‘n’ natural numbers using MLA instruction. 

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
	LDR R1, [R0]
	LDR R4, =DST
	
	ADD R2, R1, #1
	MLA R3, R1, R2, #0
	STR R3, [R4]
	
STOP
	B STOP;
	
SRC DCD 5
	AREA mydata, DATA, READWRITE
DST DCD 1
	END