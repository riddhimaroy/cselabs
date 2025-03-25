; Write an ARM assembly language program to convert a 32-bit BCD 
;number in the unpacked form into packed form. 
;0x01 0x02 into 0x12 0x34

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
		
	LDR R0, =SRC;
	MOV R1, #2
	LDR R3, =DST;
	
loop	CMP R1, #0
		BLE exit
		LDR R1, [R0], #4;
		LDR R2, [R0], #4;
		LSL R1, R1, #4;
		ORR R1, R1, R2;
		STR R1, [R3], #4;
		SUBS R1, R1, 0;
		B loop
		
exit
		
STOP
	B STOP;
	
SRC DCB 0X01, 0X02, 0X03, 0X04
	AREA mydata, DATA, READWRITE

	END