#include "ble_nrf.h"

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
//BLE_GAP_EVT_ADV_REPORT	  An advertising or scan response packet has been received.
//BLE_GAP_EVT_TIMEOUT	      Scanner has timed out.
  error_code = sd_ble_gap_scan_start ( &m_scan_param, p_adv_report_buffer );
  if ( error_code == NRF_SUCCESS )
  {
    return OK;
  }
}
/*
*
***@@ Check report after scanning and connect automaticly  
*
*/
void adv_report(ble_gap_evt_adv_report_t const * p_adv_report)
{
  uint32_t err_code;
  for ( int i = 0; i < WHITELIST_DEVICE_AMOUNT; i ++ )
  {
    if (!ble_advdata_name_find( p_adv_report->data.p_data,
                                p_adv_report->data.len,
                                p_periph_name_tab[i]))
    {
      //err_code = sd_ble_gap_scan_start(NULL, );
      //APP_ERROR_CHECK(err_code);
      return;
    }
  }
}
/*
*
***@@ Start scaning device from whitelist  
*
*/
void ble_evt_handler(ble_evt_t const * p_ble_evt, void * p_context)
{
  uint32_t err_code;

  switch (p_ble_evt->header.evt_id)
  {
    // Scanning response
    case BLE_GAP_EVT_ADV_REPORT :
      adv_report(&p_gap_evt->params.adv_report);
    break;
    // Scanning response
    case BLE_GAP_EVT_TIMEOUT :

    break;
    default:

    break;
  };
}