#ifndef UART_PROGRAM_H
#define UART_PROGRAM_H

#include "stm32f4xx_hal.h"

void UART_Init(void);  // Function to initialize UART reception
uint16_t UART_GetData(uint8_t* dataArray, uint16_t maxSize);  // Function to get the received data

#endif  // UART_PROGRAM_H
