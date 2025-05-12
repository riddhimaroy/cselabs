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
        if !(LPC_GPIO2->FIOPIN && 1<<12)
        {
            for(i=0; i<4; i++)
            {
                gpio1->fioset = i<<23;
                gpio0->fioset = tohex[arr[i]] <<4;
            }
        }
    }
}