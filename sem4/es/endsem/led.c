#include <LPC17XX.H>
unsigned int tohex[10] = {};
unsigned int arr[4] = {1, 2, 3, 4};

int main()
{
    SystemInit();
    SystemCoreClockUpdate();

    pincon
    gpio

    while(1)
    {
        for(i=0; i<256; i++)
        {
            LPC_GPIO0->FIOPIN = i<<4;
            delay();
        }
    }
}