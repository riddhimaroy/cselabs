;write an assembly programm to sort an array using selection sort

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
		LDR R2, =DST
		MOV R3, #10
		MOV R5, #0
		
copy	LDR R4, [R0, R5, LSL #2] ;og
		STR R4, [R2, R5, LSL #2] ;result arr
		ADD R5, R5, #1 ;arr index
		SUB R3, R3, #1 ;counter
		CMP R3, #0
		BGT copy
		
init	LDR R0, =DST
		MOV R1, #10; N
		MOV R2, #0; I
		
iloop 	MOV R4, R2; SMALL
		ADD R5, R2, #1

jloop 	LDR R6, [R0, R5, LSL #2]; ARR[J]
		LDR R7, [R0, R4, LSL #2]; ARR[SMALL]
		
		CMP R6, R7
		BLT ass
		BGE nass
		
ass 	MOV R4, R5

nass	ADD R5, R5, #1
		CMP R5, R1
		BLT jloop
		
		LDR R8, [R0, R2, LSL #2]; arr[i]
		STR R8, [R0, R4, LSL #2]
		LDR R9, [R0, R4, LSL #2]; ARR[SMALL]
		STR R9, [R0, R2, LSL #2]
		ADD R2, R2, #1
		CMP R2, R1
		BLT iloop

		
STOP
	B STOP;
	
SRC DCD 0x10, 0x05, 0x33, 0x24, 0x56, 0x77, 0x21, 0x04, 0x87, 0x01
	AREA mydata, DATA, READWRITE
DST DCD 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	END