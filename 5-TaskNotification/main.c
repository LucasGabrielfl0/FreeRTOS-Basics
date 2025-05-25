/* FreeRTOS Basics Part 1: Tasks and Mutex
* 1.1 How to Create tasks, 
* 1.2 Tasks running in specified Cores
* 1.3 Manage variable access using Mutex
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


}