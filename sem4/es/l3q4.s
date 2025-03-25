;Write an ARM assembly language program to convert 2-digit decimal 
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
		
		LDRB R2, [R0]; R2 = NUMBER
		CMP R2, #10
		BLT div
		
div 	CMP R2, #10
		BLT next
		ADD R3, R3, #1 ; rem
		SUB R2, R2, #10; quo
		
next 	ADD R4, R3, #30
		STR R4, [R1], #1
		CMP R2, #10
		BGT div
		
STOP
	B STOP;
	
SRC DCD 0x9B
	AREA mydata, DATA, READWRITE

DST DCD 1
	END