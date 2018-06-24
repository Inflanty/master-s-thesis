/*
**@     Author  : Jan Glos
**@@    Date    : 28.05.2018
**@@@
**@@@@  This is file main.c
**@@@   This file is provided as base for future projects.
**@@    You can modify, change, rewrite it.
**@     For sample learning.
*/

/* Standard includes. */
#include <stdio.h>

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

/* From nRF includes */
#include "bsp.h"
#include "nordic_common.h"
#include "nrf_drv_clock.h"
#include "sdk_errors.h"
#include "app_error.h"

#define TASK_DELAY          123             /* TASK delay */
#define NRF_LOG_ENABLED     1               /* Enable logs printing through jlink */

TaskHandle_t  led_toggle_task_handle;

/**@Task for LEDs toggling.
*
* BSP_BOARD_LED_0 = 0
* BSP_BOARD_LED_1 = 1
* BSP_BOARD_LED_2 = 2
* BSP_BOARD_LED_3 = 3
 */
static void vTask_toggle (void * pvParameter)
{
    UNUSED_PARAMETER(pvParameter);
    while (true)
    {
        for(int actualLED = BSP_BOARD_LED_0; actualLED <= BSP_BOARD_LED_3; actualLED ++)
        {
            bsp_board_led_invert(actualLED);    /* actualLED on */
            vTaskDelay(TASK_DELAY);             /* delay for actual flashing LED */
            bsp_board_led_invert(actualLED);    /* actualLED off */
        }
    }
}

/**@Function for Hardware Initialize
*
*
*/
void prvSetupHardware()
{
	    ret_code_t err_code;

    /* Initialize clock driver for better time accuracy in FREERTOS */
    err_code = nrf_drv_clock_init();
    APP_ERROR_CHECK(err_code);

    /* Configure LED-pins as outputs */
    bsp_board_leds_init();
}

int main(void)
{
    prvSetupHardware();
    SEGGER_SYSVIEW_Conf();

    vTaskStartScheduler();          /* Start the scheduler. */

    for( ;; );
}
