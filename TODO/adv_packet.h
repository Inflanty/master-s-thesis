#ifndef _ADV_PACKET_H_
#define _ADV_PACKET_H_
//adv_data ::  |length|Data 1 (ad_type)|Data n|
typedef enum{
  SHORTENDED_LOCAL_NAME       = 0x08,
  COMPLETE_LOCAL_NAME         = 0x09,
  DEVICE_ID                   = 0x10,
  COMPLETE_LIST_OF_SERVICE    = 0x03,
  ADV_INTERVAL                = 0x1A,
  BLE_DEV_ADDRESS             = 0x1B,
  PUBLIC_TARGET_ADDRESS       = 0x17,
  LE_ROLE                     = 0x1C,
  MESH_MESSAGE                = 0x2A,
  MESH_BEACON                 = 0x2B,
  MANUFACTURER_SPECIFIC_DATA  = 0XFF,
}generic_ad_type_t;

#endif //_ADV_PACKET_H_
