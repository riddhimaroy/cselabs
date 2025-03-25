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
	BL FIB
	LDR R2, =DST
	STR R3, [R2]
	B STOP
	
FIB 
	CMP R1, #1
	BLE BASE
	
	PUSH{R1, LR}
	SUB R1, R1, #1
	BL FIB
	MOV R4, R3
	
	SUB R1,R1, #1
	BL FIB
	POP{R1}
	
	ADD R3, R3, R4
	POP{R1, LR}
	BX LR

BASE
	MOV R3, R1
	BX LR
	
	
STOP
	B STOP;
	
SRC1 DCD 8;
SRC2 DCD 9;
	AREA mydata, DATA, READWRITE

	END