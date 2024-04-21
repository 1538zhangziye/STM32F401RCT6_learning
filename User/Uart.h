#ifndef __SERIAL_H__
#define __SERIAL_H__
#include "stdio.h"

void Uart_Init(uint32_t Baud);
void Serial_SendByte(uint8_t Data);
void Serial_SendArray(uint8_t *Data, uint8_t Length);
void Serial_SendString(char *Data);
void Serial_SendNum(uint32_t Num);
uint8_t Serial_Available(void);
uint8_t Serial_Read(void);

#endif
