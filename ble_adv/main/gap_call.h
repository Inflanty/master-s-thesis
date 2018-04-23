#ifndef _GAP_CALL_H_
#define  _GAP_CALL_H_

#include <stdint.h>
#include <stdio.h>
#include "controller.h"

#include "esp_bt.h"             //BT controller, VHCI, conf.
#include "esp_bt_main.h"        //BT stack
#include "esp_gap_ble_api.h"    //GAP conf(adv, connections)
#include "esp_log.h"            //ESP32 logs
#include "gap_call.h"

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

uint16_t scanInterval = 0;
uint16_t scanWindow = 0;
uint32_t scanDuration = 0;

uint8_t  ble_discovery_raw[ESP_BLE_ADV_DATA_LEN_MAX + ESP_BLE_SCAN_RSP_DATA_LEN_MAX];

//static uint8_t adv_config_done = 0;
#define adv_config_flag      (1 << 0)
#define scan_rsp_config_flag (1 << 1)

#ifdef CONFIG_SET_RAW_ADV_DATA
static uint8_t raw_adv_data_stat[] = {
	0x02, 0x01, 0x06,
	0x02, 0x0a, 0xeb, 0x03, 0x03, 0xab, 0xcd
};
static uint8_t raw_scan_rsp_data_stat[] = {
	0x0f, 0x09, 0x45, 0x53, 0x50, 0x5f, 0x47, 0x41, 0x54, 0x54, 0x53, 0x5f, 0x44,
	0x45, 0x4d, 0x4f
};
#endif

#ifdef PEER_ADDR

#endif

typedef enum{
	ESP_BLE_OK = 1,
	ESP_BLE_FAILED
}ble_response;

esp_ble_adv_params_t *adv_params_advertiser;

//
// Callback after gap event
//
//void esp_gap_cb(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param);
//
// Function initialized the broadcaster role
//
ble_response ble_broadcasterInit(uint8_t *raw_adv_data);
//
// Function starting broadcaster role
//
ble_response ble_broadcasterStart();
//
//	Function initilized the observer role
//
ble_response ble_observerInit();
//
// Function copy data from pointer one to pointwer two
//
ble_response ble_observerDataCopy(uint8_t  *ble_adv, uint8_t adv_data_len, uint8_t *adv_data);
//
// Function starting observer role
//
ble_response ble_observerStart();
//
//	Function pushing data
//
ble_response ble_pushData();
//
// Log function
//
void UV_LOG(char *text);
#endif /*_GAP_CALL_H_*/
