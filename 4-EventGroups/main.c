/* FreeRTOS Basics, Part 4: Event Groups
* 1.1
*
* Problem:  
* 
* 
*/

#include <stdio.h>
#include "esp_log.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/event_groups.h"

// Prototypes
void ConnectMQTT();
void ConnectWifi();
void ProcessData();


// Handle
EventGroupHandle_t ConnectHandle;
const int MQTT_bit =1;
const int Wifi_bit =1;


void app_main() 
{
    // Tasks Running without Mutex, Shows Racing Condition
    xTaskCreate(&ConnectMQTT, "MQTT", 2048, NULL, 3, NULL );
    xTaskCreate(&ConnectWifi, "WIFI", 2048, NULL, 1, NULL );
    xTaskCreate(&ProcessData, "Process", 2048, NULL, 1, NULL );

    ConnectHandle = xEventGroupCreate();

}


void ConnectMQTT()
{
    while (1)
    {
        xEventGroupSetBits(ConnectHandle, MQTT_bit);
    }
    

}

void ConnectWifi()
{
    while(1)
    {
        xEventGroupSetBits(ConnectHandle, Wifi_bit);
    }
}

void ProcessData()
{
    while(1)
    {
        xEventGroupSetBits(ConnectHandle, Wifi_bit);
    }

}