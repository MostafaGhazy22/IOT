/*
 * uart_program.c
 *
 *  Created on: Oct 18, 2024
 *      Author: Esraa
 */


#include "uart_program.h"
#include "stm32f4xx_hal.h"

#define RX_BUFFER_SIZE 256  // Define the size of the buffer

// Global variables
uint8_t rxBuffer[RX_BUFFER_SIZE];  // Buffer to store received data
volatile uint16_t writeIndex = 0;  // Index to track where to write the next byte

extern UART_HandleTypeDef huart2;  // Make sure to declare this as extern, initialized in another file

/* Initialize UART receive with interrupt */
void UART_Init(void) {
	// Start receiving data using interrupt, byte by byte
	HAL_UART_Receive_IT(&huart2, &rxBuffer[writeIndex], 1);
}

/* Callback function for UART reception complete */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	if (huart->Instance == USART2) {
		// Move to the next index in the buffer
		writeIndex = (writeIndex + 1) % RX_BUFFER_SIZE;

		// Re-initiate the UART receive interrupt for the next byte
		HAL_UART_Receive_IT(huart, &rxBuffer[writeIndex], 1);
	}
}

/* Function to retrieve received data */
uint16_t UART_GetData(uint8_t* dataArray, uint16_t maxSize) {
	uint16_t bytesAvailable = writeIndex;  // Get the number of bytes written to buffer
	uint16_t count = (bytesAvailable > maxSize) ? maxSize : bytesAvailable;

	// Copy the data from the buffer into the passed array
	for (uint16_t i = 0; i < count; i++) {
		dataArray[i] = rxBuffer[i];
	}

	// Reset the write index after the data is copied
	writeIndex = 0;

	return count;  // Return the number of bytes copied
}
