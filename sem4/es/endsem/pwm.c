#include <lpc17xx.h>


void initpwm()
{
    LPC_PINCON->PINSEL3 |= 1<<16;

    LPC_PWM1->PCR = 1<<12
    LPC_PWM1->PR = 2999
    LPC_PWM1->MR0 = 1000
    LPC_PWM1->MCR = 2
    LPC_PWM1->LER = 0xFF
    LPC_PWM1->TCR = 0x2
    LPC_PWM1->TCR = 0x9
}

void update(unsigned int pw)
{
    LPC_PWM1->MR4 = pw;
    LPC_PWM1->LER = 0XFF;
}