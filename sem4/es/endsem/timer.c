void delayms(unsigned int ms)
{
    LPC_TIM0->CTCR = 0x0
    LPC_TIM0->PR = 2999
    LPC_TIM0->TCR = 0x2
    LPC_TIM0->TCR = 0x1
    while(LPC_TIM0->TC < ms)
    LPC_TIM0->TCR = 0x0
}