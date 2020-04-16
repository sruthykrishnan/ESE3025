#include "board.h"
#include "FreeRTOS.h"
#include "task.h"

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
static void vRLEDTask1(void *pvParameters)
{
vTaskDelay(configTICK_RATE_HZ/6 );
while (1) {
Board_LED_Set(0, 0);
vTaskDelay(configTICK_RATE_HZ);
Board_LED_Set(0, 1);

vTaskDelay(3*configTICK_RATE_HZ + configTICK_RATE_HZ/2 );
}
}

/* GREEN LED toggle thread */
static void vGLEDTask2(void *pvParameters) {

vTaskDelay(configTICK_RATE_HZ + configTICK_RATE_HZ/2 );
while (1) {
Board_LED_Set(1, 0);
vTaskDelay(configTICK_RATE_HZ);
Board_LED_Set(1, 1);

vTaskDelay(3*configTICK_RATE_HZ + configTICK_RATE_HZ/2 );
}
}

/* BLUE LED toggle thread */
static void vBLEDTask3(void *pvParameters) {

vTaskDelay(2.5*configTICK_RATE_HZ + configTICK_RATE_HZ/4 );
while (1) {
Board_LED_Set(2, 0);
vTaskDelay(configTICK_RATE_HZ);
Board_LED_Set(2, 1);

vTaskDelay(3*configTICK_RATE_HZ + configTICK_RATE_HZ/2);
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

/* RED LED toggle thread */
xTaskCreate(vRLEDTask1, (signed char *) "vTaskLed1",
configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 3UL),
(xTaskHandle *) NULL);

/* GREEN LED toggle thread */
xTaskCreate(vGLEDTask2, (signed char *) "vTaskLed2",
configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 2UL),
(xTaskHandle *) NULL);

/* BLUE LED toggle thread */
xTaskCreate(vBLEDTask3, (signed char *) "vTaskLed3",
configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
(xTaskHandle *) NULL);

/* Start the scheduler */
vTaskStartScheduler();

/* Should never arrive here */
return 1;
}
