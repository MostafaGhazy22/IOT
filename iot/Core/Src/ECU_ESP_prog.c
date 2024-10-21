#include "ECU_ESP_interface.h"
#include "usart.h" // Include STM32 HAL for UART
#include "string.h"

void ESP_Send_AT_Command(const char *command) {
    HAL_UART_Transmit(&huart2, (uint8_t *)command,(uint16_t) strlen(command), HAL_MAX_DELAY);
}

void ESP_Init() {
    // Initialize ESP by sending basic AT commands
    ESP_Send_AT_Command("AT+RST\r\n");
    HAL_Delay(1000);

    // Set ESP32 to station mode
    ESP_Send_AT_Command("AT+CWMODE=1\r\n");
    HAL_Delay(1000);

    // Connect to WiFi
    ESP_Send_AT_Command("AT+CWJAP_CUR=\"MOSTAFAGHAZY1\",\"MOSTAFA#MOSTAFA\"\r\n");
    HAL_Delay(1000);
}

void ESP_Get_LED_Status() {
    // Start HTTP GET request to the server
    ESP_Send_AT_Command("AT+CIPSTART=\"TCP\",\"185.27.134.103\",80\r\n");
    HAL_Delay(1000);

    // Send GET request
    ESP_Send_AT_Command("AT+CIPSEND=98\r\n");  // Adjust 66 to the length of your GET request
    HAL_Delay(1000);

    ESP_Send_AT_Command("GET /user_files/device_status_2.txt HTTP/1.1\r\nHost: iotprog.lovestoblog.com\r\nConnection: close\r\n\r\n");
    HAL_Delay(500);
    // Receive response and process in the main loop
}
