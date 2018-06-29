#ifndef _BLE_NRF_H_
#define _BLE_NRF_H_

#include <stdio.h>
#include "ble_gap.h" // ble_gap_scan_params_t 

/* SCANING PARAMETERS */
#define SCAN_INTERVAL 100 //ms
#define SCAN_TIMEOUT 0xFFFF //0x0000 - 0xFFFF
#define SCAN_WINDOW 500
#define WHITELIST_DEVICE_AMOUNT 3

#define LOG__(traceString channel__ ,const char *srt__) vTracePrint(channel__, str__);

ble_gap_addr_t      pAddWhitelist[1];
//ble_data_t          * p_adv_report_buffer;
uint8_t             pScanData[31];
char                *p_periph_name_tab[WHITELIST_DEVICE_AMOUNT] = { "thingy",
                                                                    "sensor",
                                                                    "testdv" };
typedef enum {
  OK,
  ERROR,
  WARNING
} error_type_t;

typedef enum {
  THINGY,
  SENSOR,
  TEST_DEVICE,
  NONE
} device_type_t;

error_type_t registerDevice ( device_type_t device );
error_type_t searchForDevice ( device_type_t device );
void adv_report(ble_gap_evt_adv_report_t const * p_adv_report);
void ble_evt_handler(ble_evt_t const * p_ble_evt, void * p_context);
sd_ble_gap_scan_start(&m_scan_param);



#endif // _BLE_NRF_H_ 