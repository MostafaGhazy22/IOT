#ifndef ESP_PROG_H
#define ESP_PROG_H

#include "stm32f4xx_hal.h" // Adjust this include if using a different STM32 family

// Function to send AT command to ESP32
void ESP_Send_AT_Command(const char *command);

// Function to initialize the ESP32 (set WiFi mode, connect to WiFi)
void ESP_Init(void);

// Function to send a GET request to fetch the LED status from the server
void ESP_Get_LED_Status(void);
void ESP_Get_FAN_Status(void);
void ESP_Post_Gas_Value(uint8_t gasValue);


#endif // ESP_PROG_H
