#include <lpc17xx.h>

void lcd_init()
{
    LPC_PINCON->PINSEL1 &= ~(0XFFF<<14); //P0.23-28
    LPC_GPIO0->FIODIR |= (0X3F<<23);

    clear_ports();
    delay_lcd(30000);

    lcd_comdata(0x33, 0);
    delay_lcd(30000);
    lcd_comdata(0x32, 0);
    delay_lcd(30000);
    lcd_comdata(0x28, 0);
    delay_lcd(30000);
    lcd_comdata(0x0c, 0);
    delay_lcd(30000);
    lcd_comdata(0x06, 0);
    delay_lcd(30000);
    lcd_comdata(0x01, 0);
    delay_lcd(30000);

    return;
}

void lcd_comdata(int temp1, int type)
{
    int temp2 = temp1 & 0xF0;
    temp2 = temp2 <<19; //23-4
    write(temp2, type);
    temp2 = temp1 & 0x0F;
    temp2 = temp2<<23;
    write(temp2, type);

    delay_lcd(1000);
    return;
}

void write(int t2, int ty)
{
    clear_ports();
    LPC_GPIO0->FIOPIN = t2;

    if(ty==0)
    {
        LPC_GPIO0->FIOCLR = 1<<27;
    }
    else
        LPC_GPIO0->FIOSET = 1<<27;

    LPC_GPIO0->FIOSET = 1<<28;
    delay_lcd(25);
    LPC_GPIO0->FIOCLR = 1<<28;

    return;
}

void delay_lcd(unsigned int r)
{
    unsigned int i;
    for(i=0; i<r; i++);
    return;
}

void clear_ports()
{
    LPC_GPIO0->FIOCLR = 0X3F<<23;

    return;
}

void lcd_puts(unsigned char *str)
{
    unsigned int i = 0;
    unsigned int t;

    while(str[i]!='\0')
    {
        t = str[i];
        lcd_comdata(t, 1);
        i++;

        if(i==16)
        {
            lcd_comdata(0xc0, 0);
        }
    }
    return;
}