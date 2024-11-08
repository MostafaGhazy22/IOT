#include "ECU_ESP_interface.h"
#include "usart.h" // Include STM32 HAL for UART
#include "string.h"
#include <stdio.h>         // Include stdio.h for sprintf


void ESP_Send_AT_Command(const char *command) {
    HAL_UART_Transmit(&huart2, (uint8_t *)command,(uint16_t) strlen(command), HAL_MAX_DELAY);
}

void ESP_Init() {
    // Initialize ESP by sending basic AT commands
    ESP_Send_AT_Command("AT+RST\r\n");
    HAL_Delay(500);

    ESP_Send_AT_Command("ATE0\r\n");
    HAL_Delay(500);

    // Set ESP32 to station mode
    ESP_Send_AT_Command("AT+CWMODE=1\r\n");
    HAL_Delay(500);

    // Connect to WiFi
    ESP_Send_AT_Command("AT+CWJAP_CUR=\"MOSTAFAGHAZY1\",\"MOSTAFA#MOSTAFA\"\r\n");
    HAL_Delay(2000);
}

void ESP_Get_LED_Status() {
    // Start HTTP GET request to the server
    ESP_Send_AT_Command("AT+CIPSTART=\"TCP\",\"185.176.43.104\",80\r\n");
    HAL_Delay(700);

    // Send GET request
        ESP_Send_AT_Command("AT+CIPSEND=68\r\n");  // Adjust 66 to the length of your GET request
        HAL_Delay(700);

        ESP_Send_AT_Command("GET http://iotprog.atwebpages.com/user_files/device_status_2.txt\r\n\r\n");
        HAL_Delay(2000);

}
void ESP_Post_Gas_Value(uint8_t gasValue) {
    // Start HTTP connection to the server
    ESP_Send_AT_Command("AT+CIPSTART=\"TCP\",\"iotprog.atwebpages.com\",80\r\n");
    HAL_Delay(700);

    // Prepare POST data
    char postData[20];
    sprintf(postData, "value=%d", gasValue);
    int contentLength = strlen(postData);

    // Prepare the full HTTP POST request with dynamically calculated Content-Length
    char postRequest[256];
    sprintf(postRequest,
            "POST /control_gas.php HTTP/1.1\r\n"
            "Host: iotprog.atwebpages.com\r\n"
            "Content-Type: application/x-www-form-urlencoded\r\n"
            "Content-Length: %d\r\n"
            "Cookie: PHPSESSID=826b9b1abee731984f3c6e41bf6eb70d\r\n\r\n"
            "%s", contentLength, postData);

    // Send CIPSEND command with the actual length of the POST request
    char cipsendCommand[32];
    sprintf(cipsendCommand, "AT+CIPSEND=%d\r\n", strlen(postRequest));
    ESP_Send_AT_Command(cipsendCommand);
    HAL_Delay(700);

    // Send the actual POST request data
    ESP_Send_AT_Command(postRequest);
    HAL_Delay(700);

    // Close the connection
    ESP_Send_AT_Command("AT+CIPCLOSE\r\n");
    HAL_Delay(2000);
}
