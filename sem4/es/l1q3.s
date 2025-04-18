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
	LDR R1, =DST
	MOV R2, #5
	
loop	LDR R3, [R0], #4
		STR R3, [R1], #4
		SUB R2, R2, #1
		BNE loop

STOP
	B STOP;
	
SRC DCD 1, 2, 3, 4, 5
	AREA mydata, DATA, READWRITE

DST DCD 1
	END