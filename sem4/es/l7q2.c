//bcd down counter

#include <LPC17xx.h>

unsigned char tohex[10] = {0X3F, 0X06, 0X5B, 0X4F, 0X66, 0X6D, 0X7D, 0X07, 0X7F, 0X6F};
long int arr[4] = {9, 9, 9, 9}; // Initialize counter to 9999
unsigned int i, j;

void delay()
{
	for(j=0; j<10000; j++);
}

int main(void)
{
	LPC_PINCON->PINSEL0 &= 0XFF0000FF;
	LPC_PINCON->PINSEL3 &= 0XFFFC3FFF;
	LPC_GPIO0->FIODIR |= 0XFF0;
	LPC_GPIO1->FIODIR |= 0XF<<23;
	
	while(1)
	{
		for(arr[3]=9; arr[3]>=0; arr[3]--)
		{
			for(arr[2]=9; arr[2]>=0; arr[2]--)
		{
				for(arr[1]=9; arr[1]>=0; arr[1]--)
				{
					for(arr[0]=9; arr[0]>=0; arr[0]--)
					{
						for(i=0; i<4; i++)
						{
							LPC_GPIO1 -> FIOPIN = i<<23;
							LPC_GPIO0 -> FIOPIN = tohex[arr[i]] <<4;
							delay();
						}
					}
				}
			}
		}
		
		LPC_GPIO0 ->FIOCLR |= 0XFF0;
		delay();
	}
}