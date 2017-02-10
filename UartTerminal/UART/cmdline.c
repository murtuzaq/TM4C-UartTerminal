//*****************************************************************************
//
// cmdline.c - Functions to help with processing command lines.
//
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup cmdline_api
//! @{
//
//*****************************************************************************

#include "cmdline.h"

//*****************************************************************************
//
// Defines the maximum number of arguments that can be parsed.
//
//*****************************************************************************
#ifndef CMDLINE_MAX_ARGS
#define CMDLINE_MAX_ARGS        8
#endif

typedef enum {
	true,
	false
} CMDLINEBOOL;

int strcmp(const char *s1, const char *s2);

//*****************************************************************************
//
// An array to hold the pointers to the command line arguments.
//
//*****************************************************************************
static char *g_ppcArgv[CMDLINE_MAX_ARGS + 1];

//*****************************************************************************
//
//! Process a command line string into arguments and execute the command.
//!
//! \param pcCmdLine points to a string that contains a command line that was
//! obtained by an application by some means.
//!
//! This function will take the supplied command line string and break it up
//! into individual arguments.  The first argument is treated as a command and
//! is searched for in the command table.  If the command is found, then the
//! command function is called and all of the command line arguments are passed
//! in the normal argc, argv form.
//!
//! The command table is contained in an array named <tt>g_psCmdTable</tt>
//! containing <tt>tCmdLineEntry</tt> structures which must be provided by the
//! application.  The array must be terminated with an entry whose \b pcCmd
//! field contains a NULL pointer.
//!
//! \return Returns \b CMDLINE_BAD_CMD if the command is not found,
//! \b CMDLINE_TOO_MANY_ARGS if there are more arguments than can be parsed.
//! Otherwise it returns the code that was returned by the command function.
//
//*****************************************************************************
int
CmdLineProcess(char *pcCmdLine)
{
    char *pcChar;
    unsigned int ui8Argc;
    CMDLINEBOOL bFindArg = true;
    tCmdLineEntry *psCmdEntry;

    //
    // Initialize the argument counter, and point to the beginning of the
    // command line string.
    //
    ui8Argc = 0;
    pcChar = pcCmdLine;

    //
    // Advance through the command line until a zero character is found.
    //
    while(*pcChar)
    {
        //
        // If there is a space, then replace it with a zero, and set the flag
        // to search for the next argument.
        //
        if(*pcChar == ' ')
        {
            *pcChar = 0;
            bFindArg = true;
        }

        //
        // Otherwise it is not a space, so it must be a character that is part
        // of an argument.
        //
        else
        {
            //
            // If bFindArg is set, then that means we are looking for the start
            // of the next argument.
            //
            if(bFindArg == true)
            {
                //
                // As long as the maximum number of arguments has not been
                // reached, then save the pointer to the start of this new arg
                // in the argv array, and increment the count of args, argc.
                //
                if(ui8Argc < CMDLINE_MAX_ARGS)
                {
                    g_ppcArgv[ui8Argc] = pcChar;
                    ui8Argc++;
                    bFindArg = false;
                }

                //
                // The maximum number of arguments has been reached so return
                // the error.
                //
                else
                {
                    return(CMDLINE_TOO_MANY_ARGS);
                }
            }
        }

        //
        // Advance to the next character in the command line.
        //
        pcChar++;
    }

    //
    // If one or more arguments was found, then process the command.
    //
    if(ui8Argc)
    {
        //
        // Start at the beginning of the command table, to look for a matching
        // command.
        //
        psCmdEntry = &g_sCmdTable[0];

        //
        // Search through the command table until a null command string is
        // found, which marks the end of the table.
        //
        while(psCmdEntry->pcCmd)
        {
            //
            // If this command entry command string matches argv[0], then call
            // the function for this command, passing the command line
            // arguments.
            //
            if(!strcmp(g_ppcArgv[0], psCmdEntry->pcCmd))
            {
                return(psCmdEntry->pfnCmd(ui8Argc, g_ppcArgv));
            }

            //
            // Not found, so advance to the next entry.
            //
            psCmdEntry++;
        }
    }

    //
    // Fall through to here means that no matching command was found, so return
    // an error.
    //
    return(CMDLINE_BAD_CMD);
}


/* ANSI sez:
 *   The `strcmp' function compares the string pointed to by `s1' to the
 *   string pointed to by `s2'.
 *   The `strcmp' function returns an integer greater than, equal to, or less
 *   than zero, according as the string pointed to by `s1' is greater than,
 *   equal to, or less than the string pointed to by `s2'.  [4.11.4.2]
 */
int
strcmp(const char *s1, const char *s2)
{
    for ( ; *s1 == *s2; s1++, s2++)
	if (*s1 == '\0')
	    return 0;
    return ((*(unsigned char *)s1 < *(unsigned char *)s2) ? -1 : +1);
}

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************
