; Convert a 32-bit packed BCD number into 
;its equivalent hexadecimal number.

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
	LDR R2, =DST;
	MOV R3, #8;
	MOV R4, #0;
	LDR R1, [R0];
	
loop	CMP R3, #0
		BLE exit
		AND R5, R1, #0XF;
		LSR R1, R1, #4;
		MUL R4, R4, 10
		ADD R4, R4, R5
		ADC R6, R6, #0;
		SUBS R3, R3, #1
		
exit	STR R4, [R2], #4;
		STR R6, [R2]
		
STOP
	B STOP;
	
SRC DCD 0X16
	AREA mydata, DATA, READWRITE

	END