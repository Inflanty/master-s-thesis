/**
 * Copyright (c) 2015 - 2018, Nordic Semiconductor ASA
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
/** @file
 * @defgroup blinky_example_main main.c
 * @{
 * @ingroup blinky_example_freertos
 *
 * @brief Blinky FreeRTOS Example Application main file.
 *
 * This file contains the source code for a sample application using FreeRTOS to blink LEDs.
 *
 */

#include <stdbool.h>
#include <stdint.h>

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h" 
#include "bsp.h"
#include "nordic_common.h"
#include "nrf_drv_clock.h"
#include "sdk_errors.h"
#include "app_error.h"

/* FreeRTOS Timer handler */
TimerHandle_t   hLedTimer;
TaskHandle_t    hUnnamedTask;
QueueHandle_t   hQueue;

unsigned long ulVar = 10UL;
int             taskCounter;


/**@ TASK   
 *
 *
 *  
*/
static void TLedCircle( traceString uLog )
{
    //UNUSED_PARAMETER ( pvParameter );
    bsp_board_led_invert ( 1 );
    vTracePrint(uLog, "Hello from task 1 !");

    for (;;)
    {
    
    }
    vTaskDelete ( NULL );
}
/**@  Timer's callback function
 * 
 * 
 *
*/
void vCallbackTimer( traceString uLog )
{
    //UNUSED_PARAMETER ( pvParameter );
    bsp_board_led_invert ( 0 );
    taskCounter ++;

    if ( taskCounter == 10 )
    {
        vTracePrint(uLog, "Now, I try to reseume task 1");
        taskCounter = 0;

        if ( hQueue != 0 )
        {
          if ( xQueueSend ( hQueue, (void *) &ulVar, (TickType_t) 10 ) != pdPASS )
          {
            vTracePrint(uLog, "Can't send the queue !");
          }
        }
    }
}

/**@  MAIN
 * 
 * 
 *
*/
int main(void)
{
    ret_code_t err_code;

    /* Initialize clock driver for better time accuracy in FREERTOS */
    err_code = nrf_drv_clock_init();
    APP_ERROR_CHECK(err_code);

    /* Set taskCounter to 0 */
    taskCounter = 0;

    /* Configure LED-pins as outputs */
    bsp_board_init(BSP_INIT_LEDS);

    /* Register channel */
    traceString uLog = xTraceRegisterString("UserLog");

    /* Create a Queue */
    hQueue = xQueueCreate ( 10, sizeof( unsigned long ));  

    /* Init and start trcing */
    vTraceEnable(TRC_START);

    /* Activate deep sleep mode */
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    /* Start task for LEDS circle */
    xTaskCreate(TLedCircle, "LED Circle", 1024, uLog, tskIDLE_PRIORITY, &hUnnamedTask);

    /* Software timer create */
    hLedTimer = xTimerCreate ( "Led Timer", 100, pdTRUE, uLog, vCallbackTimer );

    /* Timer start */
    xTimerStart ( hLedTimer, 0 );

    /* Start FreeRTOS scheduler. */
    vTaskStartScheduler();

    while (true)
    {
        /* FreeRTOS should not be here... FreeRTOS goes back to the start of stack
         * in vTaskStartScheduler function. */
    }
}
