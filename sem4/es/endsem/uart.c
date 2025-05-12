void initUART()
{
    LPC->SC_PCONP = 1<<3
    LPC_PINCON->PINSEL0 = 1<<4 | 1<<6
    LPC->UART0->LCR = 3 | 1<<7
    LPC->UART0->DLL = 0X0D
    LPC->UART0->DLM = 0X0
    LPC->UART0->FDR 2<<4 | 1
    LPC->UART0->FCR = 1<<0 | 1<<1 | 1<<2
    LPC->UART0->LCR &= ~(1<<7)
}

void Uwrite(char txdata)
{
    while(!(LPC->UART0->LSR && 1<<5));
    LPC->UART0->THR = txdata;
}

void Uread()
{
    while(!(LPC->UART0->LSR && 1<<0));
    return(LPC->UART0->RBR)
}

int main()
{
    initUART();
    char msg[] = "hey";
    int i = 0;

    while(1)
    {
        while(msg[i] != '\0')
        {
            uwrite(msg[i]);
            i++;
        }
    }
}