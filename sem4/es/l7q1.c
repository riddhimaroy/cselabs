#include <LPC17xx.h>

unsigned char tohex[10] = {0X3F, 0X06, 0X5B, 0X4F, 0X66, 0X6D, 0X7D, 0X07, 0X7F, 0X6F};
long int arr[4] = {1, 2, 3, 4}; // Initialize counter to 9999
unsigned int i, j;

void delay() {
    for(j=0; j<10000; j++); // Small delay
}

int main() {
    // Configure GPIO directions
    LPC_GPIO0->FIODIR |= 0xFF0;      // P0.4 - P0.11 as output for 7-segment data
    LPC_GPIO1->FIODIR |= 0xF << 23;  // P1.23 - P1.26 as output for segment selection

    while(1) {

            for(i = 0; i < 4; i++) {
                LPC_GPIO1->FIOPIN = i << 23;           // Select the current digit
                LPC_GPIO0->FIOPIN = tohex[arr[i]] << 4; // Send BCD data
                delay();
        }
    }
}
