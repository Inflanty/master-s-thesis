#ifndef _BLE_NRF_H_
#define _BLE_NRF_H_

#include "ble_gap.h" // ble_gap_scan_params_t 

/* SCANING PARAMETERS */
#define SCAN_INTERVAL 100 //ms
#define SCAN_TIMEOUT 0xFFFF //0x0000 - 0xFFFF
#define SCAN_WINDOW 500

ble_gap_scan_params_t m_scan_param = {  .active = 1, 
                                        .channel_mask = 0, 
                                        .extended = 0, 
                                        .filter_policy = BLE_GAP_SCAN_FP_WHITELIST, 
                                        .interval = SCAN_INTERVAL, 
                                        .report_incomplete_evt = 0, 
                                        .scan_phys = BLE_GAP_PHY_AUTO, 
                                        .timeout = SCAN_TIMEOUT, 
                                        .window = SCAN_WINDOW,  };

ble_gap_addr_t                          pAddWhitelist[1];

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