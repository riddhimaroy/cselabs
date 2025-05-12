#include <LPC17xx.h>

unsigned long int cw[4] = {0x10, 0x20, 0x40, 0x80}; //p0.4, 5, 6, 7
unsigned long int acw[4] = {0x80, 0x40, 0x20, 0x10};
unsigned int i, j;

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

void initTimer0()
{
    LPC_TIM0->CTCR = 0x00;
    LPC_TIM0->TCR = 0x02;
    LPC_TIM0->PR = 2;
    LPC_TIM0->MR0 = 999;
    LPC_TIM0->MCR = 2
    LPC_TIM0->EMR = 0x20;
    LPC_TIM0->TCR = 0x01;
}

void delayms(int ms)
{
    for(int i=0; i<ms; i++)
    {
        initTimer0();
        while(!(LPC_TIM0->EMR & 1));
    }
}