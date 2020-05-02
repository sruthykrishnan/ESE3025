//============================================================================
// Name        : mutex.c
// Author      : Sruthy Krishnan
// Description : FreeRTOS blinky project with mutex API function
//============================================================================

#include "board.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

//Created the xMutex variable
xSemaphoreHandle xMutex;

void LED_clear(void)
{
Board_LED_Set(0, true);
Board_LED_Set(1, true);
Board_LED_Set(2, true);
}


static void prvSetupHardware(void)
{
SystemCoreClockUpdate();
Board_Init();
LED_clear();
}


static void LED_blinkTask( void *pvParameters )
{
int ledNum = ( int * ) pvParameters;
while (1)
{
xSemaphoreTake( xMutex, portMAX_DELAY );
Board_LED_Set(ledNum, 0);
vTaskDelay(configTICK_RATE_HZ);

Board_LED_Set(ledNum, 1);
vTaskDelay(configTICK_RATE_HZ / 2);
xSemaphoreGive( xMutex );
}
}

int main(void)
{
prvSetupHardware();
xMutex = xSemaphoreCreateMutex();

if( xMutex != NULL )
{
/* RED LED toggle thread */
xTaskCreate(LED_blinkTask, (signed char* ) "Red_LED",
configMINIMAL_STACK_SIZE, 0, (tskIDLE_PRIORITY + 1UL),
(xTaskHandle *) NULL);

/* GREEN LED toggle thread */
xTaskCreate(LED_blinkTask, (signed char* ) "Green_LED",
configMINIMAL_STACK_SIZE, 1, (tskIDLE_PRIORITY + 1UL),
(xTaskHandle *) NULL);

/* BLUE LED toggle thread */
xTaskCreate(LED_blinkTask, (signed char* ) "Blue_LED",
configMINIMAL_STACK_SIZE, 2, (tskIDLE_PRIORITY + 1UL),
(xTaskHandle *) NULL);
}
vTaskStartScheduler();
return 1;
}
