;Write a program to add two 128 bit numbers available in code memory and 
;store the result in data memory. 

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
	LDR R5, =NUM2
	LDR R11, =DST
	MOV R10, #0
	
	LDR R1, [R0], #4
	LDR R2, [R0], #4
	LDR R3, [R0], #4
	LDR R4, [R0]
	
	LDR R6, [R5], #4
	LDR R7, [R5], #4
	LDR R8, [R5], #4
	LDR R9, [R5]
	
	ADDS R10, R1, R6
	STR R10, [R11], #4
	
	ADCS R10, R2, R7
	STR R10, [R11], #4
	
	ADCS R10, R3, R8
	STR R10, [R11], #4
	
	ADCS R10, R4, R9
	STR R10, [R11], #4
	
STOP
	B STOP;
	
NUM1 DCD 1,0xFFFFFFFF,0xFFFFFFFF,4
NUM2 DCD 5,6,7,8
	AREA mydata, DATA, READWRITE
		
DST DCD 1

	END