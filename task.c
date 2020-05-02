//============================================================================
// Name        : task.c
// Author      : Sruthy Krishnan
// Description : freeRTOS blinky project with taskENTER_CRITICAL() & 
//               taskEXIT_CRITICAL() API functions
//============================================================================

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

void LED_init(void)
{
Board_LED_Set(0, true);
Board_LED_Set(1, true);
Board_LED_Set(2, true);
}

/* Sets up system hardware */
static void prvSetupHardware(void)
{
SystemCoreClockUpdate();
Board_Init();
/* Initial LED state is off */
LED_init();
}

/* RED LED toggle thread */
static void RED_LED(void *pvParameters)
{
vTaskDelay(configTICK_RATE_HZ/6 );
while (1)
{
Board_LED_Set(0, 0);
taskENTER_CRITICAL();
vTaskDelay(configTICK_RATE_HZ);
Board_LED_Set(0, 1);
taskEXIT_CRITICAL();
vTaskDelay(3*configTICK_RATE_HZ + configTICK_RATE_HZ/2 );
}
}

/* GREEN LED toggle thread */
static void GREEN_LED(void *pvParameters)
{
vTaskDelay(configTICK_RATE_HZ + configTICK_RATE_HZ/2 );
while (1)
{
Board_LED_Set(1, 0);
vTaskDelay(configTICK_RATE_HZ);
Board_LED_Set(1, 1);
vTaskDelay(3*configTICK_RATE_HZ + configTICK_RATE_HZ/2 );
}
}

/* BLUE LED toggle thread */
static void BLUE_LED(void *pvParameters)
{
vTaskDelay(2.5*configTICK_RATE_HZ + configTICK_RATE_HZ/4 );
while (1)
{
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
xTaskCreate(RED_LED, (signed char *) "R_LED_Task",
configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 3UL),
(xTaskHandle *) NULL);

/* GREEN LED toggle thread */
xTaskCreate(GREEN_LED, (signed char *) "G_LED_Task",
configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 2UL),
(xTaskHandle *) NULL);

/* BLUE LED toggle thread */
xTaskCreate(BLUE_LED, (signed char *) "B_LED_Task",
configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
(xTaskHandle *) NULL);

/* Start the scheduler */
vTaskStartScheduler();

/* Should never arrive here */
return 1;
}
