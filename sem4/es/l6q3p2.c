//3. Write a program to simulate an 8- bit ring 
//counter with key press (SW2).  

#include <LPC17XX.H>

unsigned int i, j;
unsigned int led;

int main()
{
    SystemInit();
    SystemCoreClockUpdate();

    LPC_GPIO0_FIODIR |=  0XF<<4;
    LPC_GPIO2_FIODIR &= ~(1<<12);
    led = 0x00000010;

    while(1)
    {
        if(!(LPC_GPIO2_FIOPIN & 1<<12))
        {
            if(led >= 1<<7)
                led = 0x00000010;
            
            led <<=1;
            for(j=0; j<50000; j++);
        }
    }
    
}
