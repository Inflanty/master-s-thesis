#include "ble_nrf.h"
/*
*
***@@ register device on the whitelist  
*
*/
error_type_t registerDevice ( device_type_t device )
{
  uint32_t error_code = 0;
  ble_gap_addr_t deviceAddress;

  switch( device )
  {
    case THINGY :
      deviceAddress = { BLE_GAP_ADDR_TYPE_RANDOM_PRIVATE_RESOLVABLE, {0x71,0xA2,0xEC,0xDA,0x5F,0xE0}};
      
    break;
    case SENSOR :
      deviceAddress = { BLE_GAP_ADDR_TYPE_RANDOM_PRIVATE_RESOLVABLE, {0x71,0xA2,0xEC,0xDA,0x5F,0xE1}};
      
    break;
    case TEST_DEVICE :
      deviceAddress = { BLE_GAP_ADDR_TYPE_RANDOM_PRIVATE_RESOLVABLE, {0x71,0xA2,0xEC,0xDA,0x5F,0xFF}};
      
    break;
    default:

    break;
  }
  pAddWhitelist[0] = &deviceAddress;
  error_code = sd_ble_gap_whitelist_set(pAddWhitelist , 1);
  if ( error_code == NRF_SUCCESS )
  {
    return OK;
  }
}
/*
*
***@@ Start scaning device from whitelist  
*
*/
error_type_t searchForDevice ( device_type_t device )
{
  uint32_t error_code = 0;
  ble_gap_scan_params_t m_scan_param = {.active = 1, 
                                        .channel_mask = 0, 
                                        .extended = 0, 
                                        .filter_policy = BLE_GAP_SCAN_FP_WHITELIST, 
                                        .interval = SCAN_INTERVAL, 
                                        .report_incomplete_evt = 0, 
                                        .scan_phys = BLE_GAP_PHY_AUTO, 
                                        .timeout = SCAN_TIMEOUT, 
                                        .window = SCAN_WINDOW, };

  ble_data_t p_adv_report_buffer =     {.p_data = pScanData,
                                        .len = 31, };                                        
//BLE_GAP_EVT_ADV_REPORT	  An advertising or scan response packet has been received.
//BLE_GAP_EVT_TIMEOUT	      Scanner has timed out.
  error_code = sd_ble_gap_scan_start ( &m_scan_param, p_adv_report_buffer );
  if ( error_code == NRF_SUCCESS )
  {
    return OK;
  }
}