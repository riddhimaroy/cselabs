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
		MOV R0, #1;
		
		LDR R1, =SRC1;
		LDR R2, [R1];
		
		LDR R3, =SRC2;
		LDR R4, [R3];
STOP
	B STOP;
	
SRC1 DCD 8;
SRC2 DCD 9;
	AREA mydata, DATA, READWRITE

	END


	AREA RESET, DATA, REWADONLY
	Export __Vectors
__Vectors
	DCD 0X10001000
	DCD Reset_Handler;
	ALIGN;
	AREA mycode, CODE, REWADONLY
	ENTRY
	Export Reset_Handler
Reset_Handler
	