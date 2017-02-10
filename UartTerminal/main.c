//*****************************************************************************
//
// main.c
//
//*****************************************************************************

#include "UART/UART.h"
#include "Terminal.h"



void main(void)
{
	UART_Init();

	TerminalStart();

    while(1)
    {
    	TerminalProcessCmd();
    }
}





