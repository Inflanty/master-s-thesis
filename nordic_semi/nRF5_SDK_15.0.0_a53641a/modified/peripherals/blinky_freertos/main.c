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

TimerHandle_t var_increment_handle;
uint8_t *pointToVar;

traceString channelRegister(int *data);

/**@ TASK making circle LEDs
 *
 *
 *  
*/
static void TLedCircle(void *pvParameter)
{
    for (;;)
    {
        for (uint32_t LEDnumber = 0; LEDnumber < 4; LEDnumber++)
        {
            bsp_board_led_invert(LEDnumber);
            vTaskDelay(99);
            bsp_board_led_invert(LEDnumber);
            vTaskDelay(3);
        }
    }
}
/**@ TASK Increment *pointToVar
 *
 * 
 *  
*/
static void TVarIncremant(void *pvParameter)
{
    /* Init variable */
    int someVariable = 0;

    /* Register a event */
    traceString myChannel = xTraceRegisterString("VAR 1");

    /* Store a user event with format string and data arg */
    vTracePrintF(myChannel, "Variable 1 : %u", *data);

    for (;;)
    {
        vTaskDelay(10);
        someVariable += 1;
        if (someVariable > 123)
        {
            someVariable = 0;
        }
    }
}

/**@ Function for variable register and saving
 * 
 * 
 *
*/
traceString channelRegister(int *data)
{
    /* Register a event */
    traceString myChannel = xTraceRegisterString("VAR 1");

    /* Store a user event with format string and data arg */
    vTracePrintF(myChannel, "Variable 1 : %u", *data);

    /* Return the channel string */
    return myChannel;
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

    /* Configure LED-pins as outputs */
    bsp_board_init(BSP_INIT_LEDS);

    /* Init and start trcing */
    vTraceEnable(TRC_START);

    /* Activate deep sleep mode */
    //SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    /* Variable incrementing task start */
    xTaskCreate(TVarIncremant, "Var ++", configMINIMAL_STACK_SIZE + 200, NULL, 2, &var_increment_handle);

    /* Start task for LEDS circle */
    xTaskCreate(TLedCircle, "LED Circle", configMINIMAL_STACK_SIZE + 200, NULL, 5, NULL);
    
    /* Start FreeRTOS scheduler. */
    vTaskStartScheduler();

    while (true)
    {
        /* FreeRTOS should not be here... FreeRTOS goes back to the start of stack
         * in vTaskStartScheduler function. */
    }
}
