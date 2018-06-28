#ifndef _BLE_NRF_H_
#define _BLE_NRF_H_

#include "ble_gap.h" // ble_gap_scan_params_t 

/* SCANING PARAMETERS */
#define SCAN_INTERVAL 100 //ms
#define SCAN_TIMEOUT 0xFFFF //0x0000 - 0xFFFF
#define SCAN_WINDOW 500

ble_gap_scan_params_t m_scan_param = { .active = 1, .interval = SCAN_INTERVAL, .whitelist = NULL, .timeout = SCAN_TIMEOUT, .window = SCAN_WINDOW, };

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

struct dev {

} ;
error_type_t searchForDevice ()

error_type_t searchForDevice ( device_type_t );
sd_ble_gap_scan_start(&m_scan_param);



#endif // _BLE_NRF_H_ 