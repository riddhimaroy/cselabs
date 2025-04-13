//up down counter using led

#include <lpx17xx.h>

unsigned int i, j;
unsigned int led;

int main()
{
    SystemInit();
    SystemCoreClockUpdate();

    LPC_PINCON->PINSEL0 &= ~(0XFFFF<<8);
    LPC->GPIO0->FIODIR |= 0XFF<<4;

    LPC_PINCON->PINSEL4 &= ~(0X3<<24);
    LPC->GPIO2->FIODIR &= ~(1<<12);

    while(1)
    {
        if(LPC->GPIO2_FIOPIN & 1<<12)
        {
            for(led = 255; led >= 0; led--)
            {
                LPC_GPIO0->FIOPIN = led<<4;
                for(int j = 0; j<50000; j++);
            }
        }
        else{
            for(led = 0; led < 256; led++)
            {
                LPC_GPIO0->FIOPIN = led<<4;
                for(int j = 0; j<50000; j++);
            }
        }
    }
}