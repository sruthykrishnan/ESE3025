#include "board.h"
#include "FreeRTOS.h"
#include "task.h"
#include <stdint.h>

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/* Sets up system hardware */
static void prvSetupHardware(void)
{
SystemCoreClockUpdate();
Board_Init();

/* Initial LED state is off */

Board_LED_Set(0, false);
Board_LED_Set(1, false);
Board_LED_Set(2, false);

}

/* RED LED toggle thread */
void LEDTask(void *pvParameters)
{
uint8_t LEDNumber = (uint8_t *) pvParameters;
while (1) {
Board_LED_Set(0, 0);
vTaskDelay(configTICK_RATE_HZ);
Board_LED_Set(0, 1);

vTaskDelay(3*configTICK_RATE_HZ + configTICK_RATE_HZ/2 );
}
}

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/**
 * @brief main routine for FreeRTOS blinky example
 * @return Nothing, function should not exit
 */
int main(void)
{
prvSetupHardware();
uint8_t redLEDvalue = 0;
uint8_t greenLEDvalue = 1;
uint8_t blueLEDvalue = 2;

/* RED LED toggle thread */
xTaskCreate(LEDTask, (signed char *) "Red Task",
configMINIMAL_STACK_SIZE, NULL, (void*) &redLEDvalue,
(xTaskHandle *) NULL);

/* GREEN LED toggle thread */
xTaskCreate(LEDTask, (signed char *) "Green Task",
configMINIMAL_STACK_SIZE, NULL, (void*) &greenLEDvalue,
(xTaskHandle *) NULL);

/* BLUE LED toggle thread */
xTaskCreate(LEDTask, (signed char *) "Blue Task",
configMINIMAL_STACK_SIZE, NULL, (void*) &greenLEDvalue,
(xTaskHandle *) NULL);

/* Start the scheduler */
vTaskStartScheduler();

/* Should never arrive here */
return 1;
}
