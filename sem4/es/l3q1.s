	AREA RESET, DATA, READONLY
	EXPORT __Vectors
__Vectorsbranch 
	DCD 0x10001000 ; stack pointer value when stack is empty
	DCD Reset_Handler ; reset vector
	ALIGN
	AREA mycode, CODE, READONLY
	ENTRY
	EXPORT Reset_Handler
Reset_Handler
	LDR R0, =DVD
	LDR R1, =DVS
	LDR R2, =QQ
	LDR R6, =REM
	LDR R3, [R0]
	LDR R4, [R1]
	MOV R5, #0
	
loop
	CMP R3, R4
	BLT ex
	ADD R5, R5, #1
	SUB R3, R3, R4

	BNE loop

ex
	STR R5, [R2]; quotient
	STR R3, [R6]; remainder

	B STOP;
	
DVD DCD 18;
DVS DCD 9;
	AREA mydata, DATA, READWRITE
QQ DCD 0
REM DCD 1
	
	END



	AREA RESET, DATA, READONLY
	EXPORT __Vectors
__Vectorsbranch 
	DCD 0x10001000 ; stack pointer value when stack is empty
	DCD Reset_Handler ; reset vector
	ALIGN
	AREA mycode, CODE, READONLY
	ENTRY
	EXPORT Reset_Handler
Reset_Handler
	LDR R0, =DVD;
	LDR R1, =DVS;
	LDR R0, [R0];
	LDR R1, [R1];
	LDR R2, =QQ;
	LDR R3, =REM;
	MOV R4, #0;

loop	CMP R0, R1
		BLT next
		SUBS R0, R0, R1;
		ADD R4, R4, #1;
		B loop

next	STR R4, [R2];
		STR R0, [R3];

		B STOP
	
DVD DCD 18;
DVS DCD 9;
	AREA mydata, DATA, READWRITE
QQ DCD 0
REM DCD 1
	
	END