#include <lpc17xx.h>

unsigned int i, j;
unsigned long LED = 0x00000010;

int main(void)
{
	SystemInit();
	SystemCoreClockUpdate();
	
	LPC_PINCON->PINSEL0 &= 0xFF0000FF;
	LPC->GPIO0->FIODIR |= 0x00000FF0; //output
	
	LPC_PINCON->PINSEL4 &= ~(3<<20);
	LPC_GPIO2->FIODIR &= ~(1<<10); //input
	
	while(1)
	{
		while(!(LPC_GPIO2->FIOPIN & 1<<10))
		{
			
			LPC->GPIO0->FIOCLR = 0x00000FF0;
			LPC->GPIO0->FIOSET = LED;
			
			if(LED > 0x00000800)
				LED = 0x00000010;
			else
				LED<<=1;
			for(j=0; j<1000; j++);
			
			
		}
	}
}