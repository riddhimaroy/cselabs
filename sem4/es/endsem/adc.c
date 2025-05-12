#include <lpc17xx.h>

int main()
{
    lcd_init();
    LPC_PINCON->PINSEL3 = 0x3 <<30;

    LPC_SC->PCONP = (1<<15) | (1<<12);
    
    while(1)
    {
        LPC_ADC->ADCR = (1<<5) | (1<<21) | (1<<24);
        while(LPC_ADC->ADDR5 && 1<<31);

        adct = LPC_ADC->ADDR5;
        adct = adct>>4 & 0xFFF;

        invtg = ((flaot)adct * 3.3)/0xFFF;

        sprintf(vtg, "3.2%fV", invtg);
        sprintf(dval, "%x", adct);
    }
}