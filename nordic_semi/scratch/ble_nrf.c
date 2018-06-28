#include "ble_nrf.h"
/*
***@ Function for specific devices searching
*
*
*/
error_type_t searchForDevice ( device_type_t device )
{
  uint32_t error_code = 0;
  switch( device )
  {
    case THINGY :
      ble_gap_addr_t deviceAddress = { BLE_GAP_ADDR_TYPE_RANDOM_PRIVATE_RESOLVABLE, {0x71,0xA2,0xEC,0xDA,0x5F,0xE0}};
      
    break;
    case SENSOR :
      ble_gap_addr_t deviceAddress = { BLE_GAP_ADDR_TYPE_RANDOM_PRIVATE_RESOLVABLE, {0x71,0xA2,0xEC,0xDA,0x5F,0xE1}};
      
    break;
    case TEST_DEVICE :
      ble_gap_addr_t deviceAddress = { BLE_GAP_ADDR_TYPE_RANDOM_PRIVATE_RESOLVABLE, {0x71,0xA2,0xEC,0xDA,0x5F,0xFF}};
      
    break;
    default:

    break;
  }
  pAddWhitelist[0] = &deviceAddress;
  sd_ble_gap_whitelist_set(pAddWhitelist , 1);
}