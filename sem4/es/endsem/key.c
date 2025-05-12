#include <LPC17xx.h>
unsigned char scancode[16] = {0x11, 0x21, 0x41, 0x81,
                              0x12, 0x22, 0x42, 0x82}
unsigned char ascci[16] = {'0'};

int main()
{
    sysnteminit();
    systemcoreclockupdate();

    lcd_init();
    lcd_comdata(0x80, 0);
    delay();
    lcd_puts(&msg[0]);

    while(1)
    {
        while(1)
        {
            for(rows = 0; rows <4; rows++)
            {
                if rows==1
                    var = 1<<10;
                else if 2 
                    var = 2<<10;
                
                LPC_GPIO2->FIOCLR = 0XF<<10;
                LPC_GPIO2->FIOSET = var;

                flag = 0;
                scan();

                if(flag == 1)
                    break;
                
            }

            if(flag == 1)
                break;
        }

        for(i=0; i<16; i++)
        {
            if(key == scancode[i])
                key = ascci[i];
        }
    }
}