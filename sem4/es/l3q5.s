;Write an ARM assembly language program to convert a 32 bit BCD number in 
;the unpacked form into packed form.

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
		LDRB R2, [R0], #1
		LDRB R3, [R0], #1
		LDRB R4, [R0], #1
		LDRB R5, [R0]
		
		LSL R2, R2, #4
		ORR R2, R3, R2
		LSL R2, R2, #4
		ORR R2, R4, R2
		LSL R2, R2, #4
		ORR R2, R5, R2
		
		STR R2, [R1]
		
STOP
	B STOP;
	
SRC DCD 0x01, 0x02, 0x03, 0x04
	AREA mydata, DATA, READWRITE

	END 