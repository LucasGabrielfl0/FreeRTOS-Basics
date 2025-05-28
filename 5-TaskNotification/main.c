/* FreeRTOS Basics Part 5: Task Notifications
* 1.1 H
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

static TaskHandle_t HandleReceptor = NULL;
static TaskHandle_t HandleEmissor = NULL;

void task1()
{
    while(1)
    {
        xTaskNotifyGive(HandleReceptor);
    }

}

void task2()
{
    int qunt;
    while (1)
    {
        qunt = ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        
    }
    

}


void app_main() 
{
    // Tasks Running without Mutex, Shows Racing Condition
    xTaskCreate(&task1, "FastTask", 2048, "Task1", 3, &HandleReceptor );
    xTaskCreate(&task2, "SlowTask", 2048, "Task2", 1, &HandleEmissor);

}