/**
ADD LICENCE !!!
 */


#include "sdk_config.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>
#include <ctype.h>
#include "nordic_common.h"
#include "app_timer.h"

#include "boards.h"

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "ble_lesc.h"

/**@brief Function for handling the adv_list_timer event, which refreshes the connectable devices.
 */
static void adv_list_timer_handle(void * p_context)
{
    if (is_scanning())
    {
        connect_addr_clear();
        scan_device_info_clear();
    }
}


/**@Function for initializing logging.
 */
static void log_init(void)
{

    // TODO : ret_code_t err_code = NRF_LOG_INIT(app_timer_cnt_get);
    // TODO : Chceck SEGGER_LOG function
    APP_ERROR_CHECK(err_code);
}


/**@brief Function for initializing the timer.
 *@TODO : Check the fucnction necessity
 */
static void timer_init(void)
{
    ret_code_t err_code = app_timer_init();

    APP_ERROR_CHECK(err_code);

    // Timer for refreshing scanned devices data.
    APP_TIMER_DEF(adv_list_timer);
    err_code = app_timer_create(&adv_list_timer, APP_TIMER_MODE_REPEATED, adv_list_timer_handle);
    APP_ERROR_CHECK(err_code);

    err_code = app_timer_start(adv_list_timer, FOUND_DEVICE_REFRESH_TIME, NULL);
    APP_ERROR_CHECK(err_code);
}


/**@brief Function for initializing power management.
 *@TODO : Sleep mode management
 */
static void power_management_init(void)
{
    ret_code_t err_code;
    err_code = nrf_pwr_mgmt_init();
    APP_ERROR_CHECK(err_code);
}


/**@brief Function for handling the idle state (main loop).
 *
 * @details : no datails now
 * @TODO :
 */
static void idle_state_handler(void)
{
    ret_code_t err_code;
    err_code = ble_lesc_service_request_handler();
    APP_ERROR_CHECK(err_code);
}


int main(void)
{
    power_management_init();
    log_init();
    timer_init();

    lesc_init();
    ble_m_init();
    peer_manager_init();
    bond_get();

    NRF_LOG_RAW_INFO("BLE app with command line interface example started.\r\n");
    NRF_LOG_RAW_INFO("Press Tab to view all available commands.\r\n");

    for (;;)
    {
        idle_state_handler();
    }
}
