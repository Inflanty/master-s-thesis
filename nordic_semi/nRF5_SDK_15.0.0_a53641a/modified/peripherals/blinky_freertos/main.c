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
#include "bsp.h"
#include "nordic_common.h"
#include "nrf_drv_clock.h"
#include "sdk_errors.h"
#include "app_error.h"
#include "semphr.h"

#if LEDS_NUMBER <= 2
#error "Board is not equipped with enough amount of LEDs"
#endif

#define TASK_DELAY        200           /**< Task delay. Delays a LED0 task for 200 ms */
#define TIMER_PERIOD      1000          /**< Timer period. LED1 timer will expire after 1000 ms */

TaskHandle_t  led_toggle_task_handle;   /**< Reference to LED0 toggling FreeRTOS task. */
TaskHandle_t  led1_toggle_task_handle;   /**< Reference to LED0 toggling FreeRTOS task. */
TaskHandle_t  led3_toggle_task_handle;   /**< Reference to LED0 toggling FreeRTOS task. */
TimerHandle_t led_toggle_timer_handle;  /**< Reference to LED1 toggling FreeRTOS timer. */

bool isTask1Suspended = false;

static void led1_toggle_task_function (void * pvParameter)
{
    UNUSED_PARAMETER(pvParameter);
    traceString controlMark = xTraceRegisterString("task 3");

    while (true)
    {
        ulTaskNotifyTake ( pdTRUE, portMAX_DELAY );
        bsp_board_led_invert(BSP_BOARD_LED_3);
        vTaskDelay (100);
        bsp_board_led_invert(BSP_BOARD_LED_3);
        xTaskNotifyGive ( led3_toggle_task_handle );

        if ( bsp_board_button_state_get ( BSP_BOARD_BUTTON_3 ) )
        {
            vTracePrint (controlMark, "Bye bye taks 3 !");
            isTask1Suspended = true;
            vTaskSuspend (NULL);
        }
    }
}
static void led3_toggle_task_function (void * pvParameter)
{
    UNUSED_PARAMETER(pvParameter);

    while (true)
    {
        ulTaskNotifyTake ( pdTRUE, portMAX_DELAY );
        bsp_board_led_invert(BSP_BOARD_LED_1);
        vTaskDelay (100);
        bsp_board_led_invert(BSP_BOARD_LED_1);
        xTaskNotifyGive ( led1_toggle_task_handle );
    }
}
/*
*@ task 3 definition
*
*/
static void externalTask3 ( void * pvParameter )
{
  UNUSED_PARAMETER ( pvParameter );

  traceString waterMarkMain = xTraceRegisterString("mian task");
  traceString waterMarkExternal1 = xTraceRegisterString("task 1");
  traceString waterMarkExternal2 = xTraceRegisterString("task 2");
  traceString waterMarkExternal3 = xTraceRegisterString("task 3");
  UBaseType_t uxHighWaterMark;

  for ( ;; )
  {
    vTaskDelay ( 100 );
    for ( int taskNumber = 0; taskNumber < 4; taskNumber ++ )
    {
      switch ( taskNumber )
      {
        case 0:
        /* Calculate the watermark */
        uxHighWaterMark = uxTaskGetStackHighWaterMark( led_toggle_task_handle );
        /* Send wm value */
        vTracePrintF(waterMarkMain, "Calculated Water Mark %u", uxHighWaterMark);
        break;
        case 1:
        uxHighWaterMark = uxTaskGetStackHighWaterMark( led1_toggle_task_handle ); 
        /* Send wm value */
        vTracePrintF(waterMarkExternal1, "Calculated Water Mark %u", uxHighWaterMark);
        break;
        case 2:
        uxHighWaterMark = uxTaskGetStackHighWaterMark( led3_toggle_task_handle ); 
        /* Send wm value */
        vTracePrintF(waterMarkExternal2, "Calculated Water Mark %u", uxHighWaterMark);
        break;
        case 3:
        uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL ); 
        vTracePrintF(waterMarkExternal3, "Calculated Water Mark %u", uxHighWaterMark);
        break;
      }
    }
  }

  //vTaskDelete ( NULL );
}
/**@brief LED0 task entry function.
 *
 * @param[in] pvParameter   Pointer that will be used as the parameter for the task.
 */
static void led_toggle_task_function (void * pvParameter)
{
    UNUSED_PARAMETER(pvParameter);
    vTaskDelay (111);
    bsp_board_led_invert( BSP_BOARD_LED_0 );
    xTaskNotifyGive ( led1_toggle_task_handle );

    traceString controlMark = xTraceRegisterString("toggle task");
    
    for (;;)
    {
        vTaskDelay ( 100 );
        eTaskState task1State = eTaskGetState ( led1_toggle_task_handle );

        switch (task1State){
            case eRunning:    vTracePrint (controlMark, "Task 1 state : Running");      break;
            case eReady:      vTracePrint (controlMark, "Task 1 state : Ready");        break;
            case eBlocked:    vTracePrint (controlMark, "Task 1 state : Blocked");      break;
            case eSuspended:  vTracePrint (controlMark, "Task 1 state : Suspended");    
                              if ( bsp_board_button_state_get ( BSP_BOARD_BUTTON_1 ) ) 
                                vTaskResume ( led1_toggle_task_handle );                break;
            case eDeleted:    vTracePrint (controlMark, "Task 1 state : Deleted");      break;
            case eInvalid:    vTracePrint (controlMark, "Task 1 state : Invalid");      break;
            default:          vTracePrint (controlMark, "Task 1 state : NULL! ");       break;
        }
    }
}

/**@brief The function to call when the LED1 FreeRTOS timer expires.
 *
 * @param[in] pvParameter   Pointer that will be used as the parameter for the timer.
 */
static void led_toggle_timer_callback (void * pvParameter)
{
    UNUSED_PARAMETER(pvParameter);
    bsp_board_led_invert(BSP_BOARD_LED_2);
}

int main(void)
{
    ret_code_t err_code;

    /* Initialize clock driver for better time accuracy in FREERTOS */
    err_code = nrf_drv_clock_init();
    APP_ERROR_CHECK(err_code);

    /* Configure LED-pins as outputs */
    bsp_board_init(BSP_INIT_LEDS);

    /* Configure buttons */
    bsp_board_init(BSP_INIT_BUTTONS);

    /* Create task for LED0 blinking with priority set to 2 */
    UNUSED_VARIABLE(xTaskCreate(led_toggle_task_function, "LED0", configMINIMAL_STACK_SIZE + 50, NULL, 2, &led_toggle_task_handle));
    UNUSED_VARIABLE(xTaskCreate(led1_toggle_task_function, "LED1", configMINIMAL_STACK_SIZE + 50, NULL, 2, &led1_toggle_task_handle));
    UNUSED_VARIABLE(xTaskCreate(led3_toggle_task_function, "LED3", configMINIMAL_STACK_SIZE + 50, NULL, 2, &led3_toggle_task_handle));
    UNUSED_VARIABLE(xTaskCreate(externalTask3, "task3", configMINIMAL_STACK_SIZE + 50, NULL, 2, NULL));
    
    /* Start timer for LED1 blinking */
    led_toggle_timer_handle = xTimerCreate( "LED1", TIMER_PERIOD, pdTRUE, NULL, led_toggle_timer_callback);
    UNUSED_VARIABLE(xTimerStart(led_toggle_timer_handle, 0));

    /* Activate deep sleep mode */
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    vTraceEnable( TRC_START );
    /* Start FreeRTOS scheduler. */
    vTaskStartScheduler();

    while (true)
    {
        /* FreeRTOS should not be here... FreeRTOS goes back to the start of stack
         * in vTaskStartScheduler function. */
    }
}

/**
 *@}
 **/
