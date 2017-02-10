/*
 * Terminal.h
 *
 *  Created on: Aug 19, 2016
 *      Author: mquaizar
 */

#ifndef TERMINAL_H_
#define TERMINAL_H_

void TerminalStart(void);
void TerminalProcessCmd(void);

char* CmdArg(int argN, char *argv);

#endif /* TERMINAL_H_ */
