#include <lpc17xx.h>
#include <lcdheader.c>

unsigned char msg[13] = "key pressed=";
unsigned char scan_code = {0x11, 0x21, 0x41, 0x81,
                            0x12, 0x22, 0x42, 0x82,
                            0x14, 0x24, 0x44, 0x84,
                            0x18, 0x12, 0x14, 0x18};
unsigned char ascii_code[16] = {'0','1','2','3', 
    '4','5','6','7', 
    '8','9','A','B', 
    'C','D','E','F'}; 

int main()
{
    LPC_GPIO2->FIODIR |= 0XF<<10;
    LPC_GPIO1->FIODIR &= ~(0XF<<23);
    LPC_GPIO0->FIODIR |= 0X3F<<23;

    clear_ports();
    delay_lcd(3200);
    lcd_init();

    lcd_comdata(0x80, 0);
    delay_lcd(800);
    lcd_puts(&msg[0]);

    while(1)
    {
        while(1)
        {
            for(row = 1; row<5; row++)
            {
                if(row==1)
                    var1 = 0x00000400; // bc row is p2.10-13, thsi is 10
                if(row==2)
                var1 = 0x00000800; //11th row
                if(row==3)
                var1 = 0x00001000;
                if(row==4)
                var1 = 0x00002000;

                LPC_GPIO2->FIOCLR = 0XF<<10;
                LPC_GPIO2->FIOSET = var1;
                flag = 0;
                scan();

                if(flag == 1)
                break;
            }
            if(flag==1)
            break;
        }

        for(i=0; i<16; i++)
        {
            if(key==scan_code[i])
                key = ascii_code[i];
                break;
        }

        lcd_comdata(0xc0);
        delay_lcd(800);
        lcd_puts(&key[0]);
    }
}

void scan()
{
    t = LPC_GPIO1->FIOPIN;
    t &= 0xF << 23;

    if(t != 0x00000000)
    {
        flag = 1;
        t>>=19;
        temp>>=10;
        key = t || temp;
    }
}

void scan()
{
    int t = LPC_GPIO1->FIOPIN;
    t &= 0xF<<23;

    if(t != 0x00)
    {
        flag = 1;
        t>>=19;
        temp>>=10;
        int key = t||temp;
    }
}