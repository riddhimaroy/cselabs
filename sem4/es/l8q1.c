#include <lpc17xx.h>
#include <stdio.h>

int main()
{
    SystemInit();
    SystemCoreClockUpdate();
    lcd_init();

    unsigned char m1[14] = "key pressed=";
    int x;

    lcd_comdata(0x80, 0);
    delay_lcd(800);
    lcd_puts(&m1[0]);

    
while(1){
    if(!(LPC_GPIO2->FIOPIN & 1<<12))
    {
        x = rand()%6 + 1;
        x = x+ 0x30;
        lcd_comdata(0xc0, 0);
        delay_lcd(800);
        lcd_comdata(x, 1);
    }}
}

void lcd_init()
{
    LPC_GPIO0->FIODIR |= 0X3F<<23;

    clear_ports();
    delay(30000);

    lcd_comdata(0x32, 0);
    delay_lcd(30000);
    lcd_comdata(0x31, 0);
    delay_lcd(30000);
    lcd_comdata(0x28, 0);
    delay_lcd(30000);
    lcd_comdata(0x0c, 0);
    delay_lcd(30000);
    lcd_comdata(0x6, 0);
    delay_lcd(30000);
    lcd_comdata(0x1, 0);
    delay_lcd(30000);

    return;
}

void lcd_comdata(int t, int type)
{
    unsigned int t2;

    t2 = t1 & 0xF0;
    t2 = t2<<19;
    write(t2, type);

    t2 = t1 & 0xF;
    t2 = t2<<23;
    write(t2, type);

    return;
}

void clear_ports()
{
    LPC_GPIO0->FIOCLR = 0X3F<<23;
    return;
}

void write(int t, int type)
{
    clear_ports();
    LPC_GPIO0->FIOPIN = t;

    if(type==0)
        LPC_GPIO0->FIOCLR = 1<<27;
    else
        LPC_GPIO0->FIOSET = 1<<27;

    LPC_GPIO0->FIOSET = 1<<28;
    delay_lcd(30000);
    LPC_GPIO0->FIOCLR = 1<<28;

    return;
}

void delay_lcd(int ms)
{
    for(int i=0; i<ms; i++);
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
}