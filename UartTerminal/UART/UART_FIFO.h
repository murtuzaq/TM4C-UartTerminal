/*
 * UART_FIFO.h
 *
 *  Created on: Aug 5, 2016
 *      Author: mquaizar
 */

#ifndef UART_FIFO_H_
#define UART_FIFO_H_

typedef char txDataType;

void TxFifo_Init(void);
int TxFifo_Put(txDataType data);
int TxFifo_Get(txDataType *datapt);
unsigned short TxFifo_Size(void);

void RxFifo_Init(void);
int RxFifo_Put(txDataType data);
int RxFifo_Get(txDataType *datapt);
unsigned short RxFifo_Size(void);

#endif /* UART_FIFO_H_ */
