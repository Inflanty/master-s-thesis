#include "gap_call.h"

void esp_gap_cb(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param)
{
	//uint8_t *adv_name = NULL;
	//uint8_t adv_name_len = 0;
	esp_ble_gap_cb_param_t *scan_result = (esp_ble_gap_cb_param_t *)param;
	switch (event)
	{
	case ESP_GAP_BLE_ADV_DATA_SET_COMPLETE_EVT          :
	UV_LOG("GAP CALLBACK :: Advertising parameters complete");
	#ifdef BROADCASTER_ROLE
	if(ble_broadcasterStart() == ESP_BLE_OK){ ; }
	else { ; }
	#endif
	break;
	case ESP_GAP_BLE_SCAN_RSP_DATA_SET_COMPLETE_EVT     : break;
	case ESP_GAP_BLE_SCAN_PARAM_SET_COMPLETE_EVT        :
	UV_LOG("GAP CALLBACK :: Scan parameters complete");
	#ifdef OBSERVER_ROLE
	if(ble_observerStart() == ESP_BLE_OK){ ; }
	else{ ; }
	#endif
	break;
	case ESP_GAP_BLE_SCAN_RESULT_EVT										:
		switch (scan_result->scan_rst.search_evt)
		{
			case ESP_GAP_SEARCH_INQ_RES_EVT             		:break;
			case ESP_GAP_SEARCH_INQ_CMPL_EVT            		:break;
			case ESP_GAP_SEARCH_DISC_RES_EVT            		:break;
			case ESP_GAP_SEARCH_DISC_BLE_RES_EVT        		:break;
			case ESP_GAP_SEARCH_DISC_CMPL_EVT           		:
				if ((scan_result->scan_param_cmpl.status) == ESP_BT_STATUS_SUCCESS)
				{
					uint8_t adv_data[scan_result->scan_rst.adv_data_len];
					ble_observerDataCopy(scan_result->scan_rst.ble_adv, scan_result->scan_rst.adv_data_len, adv_data);
					UV_LOG("GAP CALLBACK :: Scan RESULT ready");
				}
				break;
			case ESP_GAP_SEARCH_DI_DISC_CMPL_EVT        		:
				if ((scan_result->scan_param_cmpl.status) == ESP_BT_STATUS_SUCCESS)
				{
					uint8_t adv_data[scan_result->scan_rst.adv_data_len];
					ble_observerDataCopy(scan_result->scan_rst.ble_adv, scan_result->scan_rst.adv_data_len, adv_data);
					UV_LOG("GAP CALLBACK :: Scan RESULT ready");
				}
				break;
			case ESP_GAP_SEARCH_SEARCH_CANCEL_CMPL_EVT  		:break;
		}
	break;
	case ESP_GAP_BLE_ADV_DATA_RAW_SET_COMPLETE_EVT      :
	UV_LOG("GAP CALLBACK :: Advertising RAW parameters complete");
	#ifdef BROADCASTER_ROLE
	int(ble_broadcasterStart() == ESP_BLE_OK){ ; }
	else { ; }
	#endif
	break;
	default: break;
	}
}
ble_response ble_broadcasterInit(uint8_t *raw_adv_data)
{
  adv_params_advertiser -> adv_int_min = 0x2000;
  adv_params_advertiser -> adv_int_max = 0x4000;
  adv_params_advertiser -> adv_type = ADV_TYPE_IND;                                  /*!< Advertising type */
  adv_params_advertiser -> own_addr_type = BLE_ADDR_TYPE_PUBLIC;                     /*!< Owner bluetooth device address type */
  #ifdef PEER_ADDR
  adv_params_advertiser -> peer_addr[0] = 0x00;                                      /*!< Peer device bluetooth device address */
  adv_params_advertiser -> peer_addr[1] = 0x00;
  adv_params_advertiser -> peer_addr[2] = 0x00;
  adv_params_advertiser -> peer_addr[3] = 0x00;
  adv_params_advertiser -> peer_addr[4] = 0x00;
  adv_params_advertiser -> peer_addr[5] = 0x00;
  adv_params_advertiser -> peer_addr_type = BLE_ADDR_TYPE_PUBLIC;                    /*!< Peer device bluetooth device address type */
  #endif
  adv_params_advertiser -> channel_map = ADV_CHNL_ALL;                               /*!< Advertising channel map */
  adv_params_advertiser -> adv_filter_policy = ADV_FILTER_ALLOW_SCAN_ANY_CON_ANY;    /*!< Advertising filter policy */

  #ifdef CONFIG_SET_RAW_ADV_DATA
		esp_err_t raw_adv_ret = esp_ble_gap_config_adv_data_raw(raw_adv_data, sizeof(raw_adv_data));
		if (raw_adv_ret) {
			ESP_LOGE(GATTS_TAG, "config raw adv data failed, error code = %x ", raw_adv_ret);
		}
		adv_config_done |= adv_config_flag;
		esp_err_t raw_scan_ret = esp_ble_gap_config_scan_rsp_data_raw(raw_scan_rsp_data, sizeof(raw_scan_rsp_data));
		if (raw_scan_ret) {
			ESP_LOGE(GATTS_TAG, "config raw scan rsp data failed, error code = %x", raw_scan_ret);
		}
		adv_config_done |= scan_rsp_config_flag;
		#endif

		return ESP_BLE_OK;
}
ble_response ble_broadcasterStart()
{
	//You can start broadcasting there
	if(esp_ble_gap_start_advertising (adv_params_advertiser))
	{
		return ESP_BLE_OK;
	}
	return ESP_BLE_FAILED;
}
ble_response ble_observerInit()
{
	esp_ble_scan_params_t scan_params = {.scan_type = BLE_SCAN_TYPE_PASSIVE,
		.own_addr_type = BLE_ADDR_TYPE_PUBLIC, .scan_filter_policy = BLE_SCAN_FILTER_ALLOW_ALL,
		.scan_interval = scanInterval, .scan_window = scanWindow,
	};

	if(esp_ble_gap_set_scan_params(&scan_params) == ESP_OK)
	{
		return ESP_BLE_OK;
	}
	return ESP_BLE_FAILED;
}
ble_response ble_observerDataCopy(uint8_t  *ble_adv, uint8_t adv_data_len, uint8_t *adv_data)
{
	for(int i = 0; i < adv_data_len; i ++)
	{
		*adv_data = 	*ble_adv;
		adv_data	++	;
		ble_adv 			++	;
	}
	return ESP_BLE_OK;
}
ble_response ble_observerStart()
{
	//Scan params set,
	//you can start observating
	if(esp_ble_gap_start_scanning(scanDuration) == ESP_OK)
	{
			return ESP_BLE_OK;
	}
	return ESP_BLE_FAILED;
}
void UV_LOG(char *text)
{
	printf(":: LOG :: ");
	printf(CYN"%s/n"RESET, text);
}

/////////////////////////////////////////////////////////////////////////////////// NOTES
/*
void esp_gap_cb(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param)
{
	uint8_t *adv_name = NULL;
	uint8_t adv_name_len = 0;
	switch (event) {
  #ifdef CONFIG_SET_RAW_ADV_DATA
  case ESP_GAP_BLE_ADV_DATA_RAW_SET_COMPLETE_EVT:
  	adv_config_done &= (~adv_config_flag);
  	if (adv_config_done==0) {
  		esp_ble_gap_start_advertising(&adv_params_user);
  	}
  	break;
  	case ESP_GAP_BLE_SCAN_RSP_DATA_RAW_SET_COMPLETE_EVT:
  	adv_config_done &= (~scan_rsp_config_flag);
  	if (adv_config_done==0) {
  		esp_ble_gap_start_advertising(&adv_params);
  	}
  	break;
  #else
	case ESP_GAP_BLE_SCAN_PARAM_SET_COMPLETE_EVT: {
		//esp_ble_gap_start_scanning(scanDuration);
		break;
	}
	case ESP_GAP_BLE_SCAN_START_COMPLETE_EVT:
		//scan start complete event to indicate scan start successfully or failed
		if (param->scan_start_cmpl.status != ESP_BT_STATUS_SUCCESS) {
			ESP_LOGE(GATTC_TAG, "scan start failed, error status = %x",
					param->scan_start_cmpl.status);
			break;
		}
		ESP_LOGI(GATTC_TAG, "scan start success")
		;

		break;
	case ESP_GAP_BLE_SCAN_RESULT_EVT:
			break;
		case ESP_GAP_SEARCH_INQ_CMPL_EVT:
			break;
		default:
			break;
		}
		break;
	}

	case ESP_GAP_BLE_SCAN_STOP_COMPLETE_EVT:
		if (param->scan_stop_cmpl.status != ESP_BT_STATUS_SUCCESS) {
			ESP_LOGE(GATTC_TAG, "scan stop failed, error status = %x",
					param->scan_stop_cmpl.status);
			break;
		}
		ESP_LOGI(GATTC_TAG, "stop scan successfully")
		;
		break;

	case ESP_GAP_BLE_ADV_STOP_COMPLETE_EVT:
		if (param->adv_stop_cmpl.status != ESP_BT_STATUS_SUCCESS) {
			ESP_LOGE(GATTC_TAG, "adv stop failed, error status = %x",
					param->adv_stop_cmpl.status);
			break;
		}
		ESP_LOGI(GATTC_TAG, "stop adv successfully")
		;
		break;
	case ESP_GAP_BLE_UPDATE_CONN_PARAMS_EVT:
		ESP_LOGI(GATTC_TAG,
				"update connetion params status = %d, min_int = %d, max_int = %d,conn_int = %d,latency = %d, timeout = %d",
				param->update_conn_params.status,
				param->update_conn_params.min_int,
				param->update_conn_params.max_int,
				param->update_conn_params.conn_int,
				param->update_conn_params.latency,
				param->update_conn_params.timeout)
		;
		break;
	default:
		break;
	}
}*/
