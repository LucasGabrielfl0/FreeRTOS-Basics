/* FreeRTOS Basics Part 3: Queue
*
* Problem:
*

*/

#include <stdio.h>
#include "esp_log.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

void Read_Temperature()
{

    while(1){

    }
}

void Read_Pressure()
{
    while(1){
        
    }
}

void LogData()
{
    while(1){
        
    }
}

void app_main() 
{
    // Tasks
    xTaskCreate(&Read_Temperature, "Temperature", 2048, NULL, 2, NULL );
    xTaskCreate(&Read_Pressure   , "Pressure"   , 2048, NULL, 2, NULL );
    xTaskCreate(&LogData         , "Logger"     , 2048, NULL, 3, NULL );
}