/* FreeRTOS Basics Part 3: Queues
* 1.1 How to Create tasks, 
* 1.2 Tasks running in specified Cores
* 1.3 Manage variable access using Mutex
* Problem: You have a temperature sensor that has a 100 ms sample period, 
* However, you only log the data every 1s, along with the average temperature
* 
*/
#include <stdio.h>
#include "esp_log.h"
#include "esp_timer.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

// DEBUG MODE
#define DEBUG_MODE 1        // 0 if not

#if DEBUG_MODE
    #define DEBUG_PRINT(fmt, ...) ESP_LOGI("DEBUG", fmt, ##__VA_ARGS__)
#else
    #define DEBUG_PRINT(fmt, ...) // Nothing
#endif




// Prototypes
void ProcessTemp();
void LogData();
void ISR_ADC_Callback();

// Global Variables
float SumAvg =0;
static uint32_t last_time = 0;
uint16_t count =0;


// Handles
QueueHandle_t TemperatureQueue;


void app_main() 
{
    // Queue for 13 ints (12 temp, 1 temp avg)
    TemperatureQueue = xQueueCreate(13, sizeof(uint16_t));

    // Tasks
    xTaskCreate(&ProcessTemp  , "Temperature" , 4096, NULL, 10, NULL );
    // xTaskCreate(&LogData      , "Logger"      , 2048, NULL, 3, NULL );
    

    // Configure and start periodic timer
    const esp_timer_create_args_t adc_timer_args = 
    {
        .callback = &ISR_ADC_Callback,
        .name = "adc_timer"
    };

    esp_timer_handle_t adc_timer;
    esp_timer_create(&adc_timer_args, &adc_timer);
    esp_timer_start_periodic(adc_timer, 10000);  // 10,000 us = 10 ms

}


// Reads ADC every 10 ms
void ISR_ADC_Callback(){
    // int Read1 =1;
    uint16_t Temp= count;
    count++;
    BaseType_t xHigherPriorityTaskWoken = pdTRUE;
    
    if (count>4095)
    {
        count = 0;
    }
    // Sends Temperature to Queue
    xQueueSendFromISR(TemperatureQueue, &Temp, &xHigherPriorityTaskWoken);
    
    // if (xHigherPriorityTaskWoken) {
    //     portYIELD_FROM_ISR();
    // }
    // Adds it to Avg
    // SumAvg +=1;

    // uint32_t now = xTaskGetTickCount() * portTICK_PERIOD_MS;
    // DEBUG_PRINT("Time since last: %lu ms\n", now - last_time);
    // last_time = now;
    DEBUG_PRINT("ISR CALLED");
    portYIELD_FROM_ISR();

    //
    // if (xHigherPriorityTaskWoken) {
    // portYIELD_FROM_ISR();
    // }
}

// Wait for ADC, then process data and saves in the Queue
void ProcessTemp(){
    uint8_t TempMsg;
    uint16_t Adc12b;

    while(1)
    {
        // Waits for new ADC value
        xQueueReceive(TemperatureQueue,&Adc12b, portMAX_DELAY);
        DEBUG_PRINT("TASK CALLED");
        
        TempMsg = (uint8_t)(Adc12b >> 4);        // [0 - 4095] -> [0 - 255]
        SumAvg +=Adc12b;                         // Sum of all Temperatures
        
        // DEBUG_PRINT("12bits: %d , 8bits: %d, Voltage: %.2f, Temperature: %.2f", 
        // Adc12b, 
        // TempMsg, 
        // (float)(Adc12b)*3.3/4095.0,
        // (float)(TempMsg)*60.0/255.0
        // );

        // Changes Mux port

        uint32_t now = xTaskGetTickCount() * portTICK_PERIOD_MS;
        DEBUG_PRINT("Time since last: %lu ms\n", now - last_time);
        last_time = now;

        // Send to Queue
        // xQueueSend(TemperatureQueue, &TempMsg, 0);
            
    }

}


// // Logs Data every 100 ms
// void LogData()
// {
//     int TempAvg =0;
//     while(1)
//     {
        
//         // if(xQueueReceive(sensorQueue, ))
//         // {
//         // // Log Last 10 Temperature values
//         // // Log Average of the temperature
//         // // Log Pressure
//         // }
//         // else
//         // {

//         // }

//         // Average
//         TempAvg = (int)(SumAvg/12);             // Get Avg
//         TempAvg = (uint8_t)(TempAvg >> 4);      // [0 - 4095] -> [0 - 255]

//         // Log all 2 temperature values + Average via UART (As ints)

//     }
// }


