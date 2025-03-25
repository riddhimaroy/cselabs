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
	LDR R0, =NUM1
	LDR R1, =NUM2
	LDR R2, =DST
	
	LDR R3, [R0]
	LDR R4, [R1]
	SUBS R5, R3, R4
	BMI neg
	STR R5, [R2]
	
neg
	RSB R5, R5, #0
	
	
STOP
	B STOP;
	
NUM1 DCD 5;
NUM2 DCD 9;
	AREA mydata, DATA, READWRITE
		
DST DCD 1

	END