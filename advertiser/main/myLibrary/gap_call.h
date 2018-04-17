#ifndef _GAP_CALL_H_
#define  _GAP_CALL_H_

uint16_t scanInterval = 0;
uint16_t scanWindow = 0;
uint32_t scanDuration = 0;

uint8_t  ble_discovery_raw[ESP_BLE_ADV_DATA_LEN_MAX + ESP_BLE_SCAN_RSP_DATA_LEN_MAX];

static uint8_t adv_config_done = 0;
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

void esp_gap_cb(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param);
void esp_ble_gap_init_broadcasting(uint8_t *raw_adv_data);

void esp_ble_gap_init_observating();

void ble_discovery_write(uint8_t  *ble_adv, uint8_t adv_data_len, uint8_t *adv_data_len);

#endif /*_GAP_CALL_H_*/
