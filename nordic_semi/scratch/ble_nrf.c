#include "ble_nrf.h"
/*
***@ Function for specific devices searching
*
*
*/
error_type_t searchForDevice ( device_type_t device )
{
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
}