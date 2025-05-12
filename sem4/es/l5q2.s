; find factorial of an unsigned number

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
	MOV R3, #1
	BL FACT
	LDR R2, =DST
	STR R3, [R2]
	B STOP
	
FACT	CMP R1, #0
		BEQ BASE
		
		PUSH{R1, LR}
		SUBS R1, R1, #1
		BL FACT
		POP{R1}
		
		MUL R3, R3, R1
		BX LR
		
BASE	MOV R3, #1
		BX LR
		
STOP
	B STOP;
	
SRC DCD 5
	AREA mydata, DATA, READWRITE
DST DCD 0
	END


	ldr r0, [src]
	mov r3, 1
	bl factorialstr

fact 	cmp r1, #0
		beq BASE

		push{r1, lr}
		subs r1, r1, #1
		bl fact
		pop{r1}

		mul r3, r3, r1
		bx lr

BASE	mov r3, #1
		bx