//burst mode

//reading from addr5 in software mode

#include <LPC17xx.h>
#include <stdio.h>
#include <lcdheader.c>

int main()
{
    SystemInit();
    SystemCoreClockUpdate();

    LPC_SC->PCONP |= (1<<15);
    LPC_SC->PCONP |= (1<<12);

    lcd_init();

    LPC_PINCON->PINSEL3 |= 0X3 <<30;
    lcd_puts(&msg[0]); //for both

    LPC_ADC->ADCR = (1<<5) || (1<<21) || (1<<16); //THE CHANGE IN BURST

    while(1)
    {

        while(!(LPC_ADC->ADDR5 &(1<<31)));

        adc_temp = LPC_ADC->ADDR5;
        adc_temp = (adc_temp>>4) & 0xFFF;

        in_vtg = ((float)adc_temp *3.3)/0xFFF;

        sprintf(vtg, "%3.2fV", in_vtg);
        sprintf(dval, "%x", adc_temp);

        for(i=0; i<2000; i++);
        lcd_puts() again
    }
}