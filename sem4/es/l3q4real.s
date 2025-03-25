;Write an ARM assembly language program to convert 2-digit hexadecimal
;number into ascii format. 

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
	
	LDRB R2, [R0] ;holds the number
	AND R3, R2, #0x0F
	
	CMP R3, #10
	BLT dec
	BGE hex
 
return	LSL R2, R2, #1
		AND R3, R2, #0x0F
	
		CMP R3, #10
		BLT dec
		BGE hex
	
dec		ADD R3, R3, #30
		STR R3, [R1], #4
		CMP R2, #16
		BGE return
		
hex  	ADD R3, R3, #37
		STR R3, [R1], #4
		CMP R2, #16
		BGE return
	
STOP
	B STOP;
	
SRC1 DCD 8;
SRC2 DCD 9;
	AREA mydata, DATA, READWRITE

	END