/*
Author  : JAN GLOS
Date    : 8.04.2018

Master's thesis
*/
#include <stdio.h>
#include "nvs.h"
#include "nvs_flash.h"
#include "controller.h"

#include "esp_bt.h"             //BT controller, VHCI, conf.
#include "esp_bt_main.h"        //BT stack
#include "esp_gap_ble_api.h"    //GAP conf(adv, connections)
#include "esp_log.h"            //ESP32 logs
#include "gap_call.h"

//#define PEER_ADDR
//#define CONFIG_SET_RAW_ADV_DATA
//#define NO_LOG
//#define OBSERVER_ROLE
//#define BROADCASTER_ROLE

//System_var
//char *MYLOG = "SYSTEM_LOG";
//char *ERLOG = "ERROR LOG";

#ifdef NO_LOG //NO LOGS FROM ESP
esp_log_level_set("*", ESP_LOG_NONE);
#endif

void esp_gap_cb(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param)
{

}

void app_main(){
  esp_err_t ret;

  ret = nvs_flash_init();
  if(ret == ESP_ERR_NVS_NO_FREE_PAGES){
    ESP_ERROR_CHECK(nvs_flash_erase());
    ret = nvs_flash_init();
  }
  ESP_ERROR_CHECK(ret);

  esp_bt_controller_config_t bt_config = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
  ret = esp_bt_controller_init(&bt_config);
  if(ret){
    //ER_LOG(ERLOG, "Initialize controller failed !");
    return;
  }

  ret = esp_bt_controller_enable(ESP_BT_MODE_BLE);
  if(ret){
    ///ER_LOG(ERLOG, "Enable controller failed !");
    return;
  }

  ret = esp_bluedroid_init();
  if(ret){
    //ER_LOG(ERLOG, "Initialize bluetooth failed !");
    return;
  }

  ret = esp_bluedroid_enable();
  if(ret){
    //ER_LOG(ERLOG, "Enable bluetooth failed !");
    return;
  }

  ret = esp_ble_gap_register_callback(esp_gap_cb);
  if(ret){
    //ER_LOG(ERLOG, "GAP register error");
    return;
  }
}
