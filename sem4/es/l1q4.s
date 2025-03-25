;Reverse an array of ten 32 bit numbers in the memory. 

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
	ADD R1, R0, #36
	MOV R2, #5
	
loop 	
	LDR R3, [R0]
	LDR R4, [R1]
	
	STR R4, [R0]
	STR R3, [R1]
	
	SUBS R1, R1, #4
	ADD R0, R0, #4	
	
	SUBS R2, R2, #1
	BNE loop

STOP
	B STOP;
	

	AREA mydata, DATA, READWRITE

SRC DCD 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
	END