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

//proper code

#include <LPC17xx.h>
#include <stdio.h>
#include "AN_LCD.h"  // Assumed custom LCD header used in your setup

unsigned long adc_temp;
unsigned int i;
float in_vtg;
unsigned char vtg[7], dval[7];   // Buffers for voltage string and ADC hex value
unsigned char Msg3[11] = {"ANALOG IP:"};
unsigned char Msg4[12] = {"ADC OUTPUT:"};

int main(void)
{
    SystemInit();
    SystemCoreClockUpdate();

    // Power to GPIO and ADC peripheral
    LPC_SC->PCONP |= (1 << 15);    // Power up GPIO
    LPC_SC->PCONP |= (1 << 12);    // Power up ADC

    lcd_init();                    // Initialize LCD

    // Configure P1.31 as AD0.5
    LPC_PINCON->PINSEL3 |= (0x3 << 30);   // P1.31 -> AD0.5

    // LCD static messages
    lcd_comdata(0x80, 0);         // First line start
    delay_lcd(800);
    lcd_puts(&Msg3[0]);           // "ANALOG IP:"

    lcd_comdata(0xC0, 0);         // Second line start
    delay_lcd(800);
    lcd_puts(&Msg4[0]);           // "ADC OUTPUT:"

    // Configure ADC in Burst Mode (no START bits)
    LPC_ADC->ADCR = (1 << 5)      // Select channel 5 (AD0.5)
                  | (1 << 16)     // BURST mode
                  | (1 << 21);    // PDN = Power ON

    while (1)
    {
        // Wait until conversion is complete for AD0.5
        while (!(LPC_ADC->ADDR5 & (1 << 31)));  // DONE bit

        // Read and extract ADC result
        adc_temp = LPC_ADC->ADDR5;
        adc_temp = (adc_temp >> 4) & 0xFFF;

        // Calculate voltage
        in_vtg = (((float)adc_temp * 3.3) / 0xFFF);

        // Format strings
        sprintf(vtg, "%3.2fV", in_vtg);
        sprintf(dval, "%X", adc_temp);

        // Short delay
        for (i = 0; i < 2000; i++);

        // Display voltage
        lcd_comdata(0x89, 0);
        delay_lcd(800);
        lcd_puts(&vtg[0]);
                                                                        
        // Display ADC hex
        lcd_comdata(0xC8, 0);
        delay_lcd(800);
        lcd_puts(&dval[0]);

        // Delay before next update
        for (i = 0; i < 200000; i++);
    }
}
