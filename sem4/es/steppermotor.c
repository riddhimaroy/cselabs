#include <LPC17xx.h>

unsigned long int cw[4] = {0x10, 0x20, 0x40, 0x80};
unsigned long int acw[4] = {0x80, 0x40, 0x20, 0x10};

int main()
{
    SystemInit();
    SystemCoreClockUpdate();

    LPC_GPIO0->FIODIR |= 0XF<<4;

    while(1)
    {
        rotate_cw(50);
        for(i=0; i<60000; i++);

        rotate_acw(50);
        for(i=0; i<60000; i++);
    }
}

rotate_cw(int steps)
{
    for(i=0; i<steps; i++)
    {
        for(j=0; j<4; j++)
        {
            LPC_GPIO0->FIOSET = cw[j];
            for(k=0; k<3000; k++);
        }
    }
}

rotate_acw(int steps)
{
    for(i=0; i<steps; i++)
    {
        for(j=0; j<4; j++)
        {
            LPC_GPIO0->FIOSET = acw[j];
            for(k=0; k<3000; k++);
        }
    }
}