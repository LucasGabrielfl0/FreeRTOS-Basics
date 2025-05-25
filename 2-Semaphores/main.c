/* FreeRTOS Basics Part 2: Semaphores
* 2.1 Semaphores
* 2.2 Binary Sempahores
* 2.3 Counting Semaphores
*/
#include <stdio.h>
#include "esp_log.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

void task1()
{

}

void task2()
{

}

void task_core1()
{

}

void task_core2()
{

}

void app_main() 
{
    // Tasks
    xTaskCreate(&task1, "FastTask", 2048, "Task1", 3, NULL );
    xTaskCreate(&task2, "SlowTask", 2048, "Task2", 1, NULL );

    //
}