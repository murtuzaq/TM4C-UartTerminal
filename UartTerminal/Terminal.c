/*
 * Terminal.c
 *
 *      Author: mquaizar
 */


#include "Terminal.h"
#include "UART/UART.h"
#include "UART/cmdline.h"


const char ProgramIdentity[] = "TM4C123 Terminal Interface";

extern const char* Legal;
extern const char* Version;

const unsigned char prompt[] = "\n\rTM4C:> ";


static char g_cInput[100];

int Cmd_help(int argc, char *argv[]);

//*****************************************************************************
//
// This is the table that holds the command names, implementing functions,
// and brief description.
//
//*****************************************************************************
tCmdLineEntry g_sCmdTable[] =
{
    { "help",   Cmd_help,   "   : Display list of commands" },
    { "h",      Cmd_help,   "   : alias for help" },
    { "?",      Cmd_help,   "   : alias for help" },


    { 0, 0, 0 }
};


void TerminalStart(void)
{
    //
    // Say Hello.
    //
	UART_OutString("\n\r");
	UART_OutString((char *)ProgramIdentity);
	UART_OutString("\n\r");
	UART_OutString((char *)Legal);
	UART_OutString("\n\r");
	UART_OutString((char *)Version);
	UART_OutString("\n\r");
	UART_OutString("Type 'help' for a list of commands\n");

	UART_OutString((char *)prompt);
}

void TerminalProcessCmd(void)
{
	UART_InString(g_cInput, 100);

	// Pass the line from the user to the command processor.
	// It will be parsed and valid commands executed.
	//
	CmdLineProcess(g_cInput);

	//exit with a command prompt
	UART_OutString((char *)prompt);
}


//*****************************************************************************
//
//	Command Line help Function
//	This function implements the "help" command.  It prints a simple list
//	of the available commands with a brief description.
//
//*****************************************************************************
int Cmd_help(int argc, char *argv[])
	{
    tCmdLineEntry *pEntry;

    //
    // Print some header text.
    //
    UART_OutString("\n\r");
    UART_OutString("Available commands\n\r");
    UART_OutString("------------------\n\r");

    //
    // Point at the beginning of the command table.
    //
    pEntry = &g_sCmdTable[0];

    //
    // Enter a loop to read each entry from the command table.  The
    // end of the table has been reached when the command name is NULL.
    //
    while(pEntry->pcCmd)
    {
        //
        // Print the command name and the brief description.
        //
    	UART_OutString((char *)pEntry->pcCmd);
    	UART_OutString((char *)pEntry->pcHelp);
    	UART_OutString("\n\r");
        //
        // Advance to the next entry in the table.
        //
        pEntry++;

    }

    //
    // Return success.
    //
    return(0);
	} //end cmd line proc help()

