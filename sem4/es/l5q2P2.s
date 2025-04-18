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
		BL FACT
		LDR R2, =DST
		STR R3, [R2]
		B STOP
		
FACT	CMP R1, #0
		BEQ base
		
		PUSH{R1, LR}
		SUB R1, R1, #1
		BL FACT
		POP{R1}
		MUL R3, R3, R1
		POP{LR}
		BX LR
		
base	MOV R3, #1
		BX LR
		
		
STOP
	B STOP;
	
SRC DCD 5
	AREA mydata, DATA, READWRITE

	END