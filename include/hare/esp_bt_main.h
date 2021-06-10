#ifndef HARE_ESP_BT_MAIN_H
#define HARE_ESP_BT_MAIN_H

#include <esp_bt_main.h>

/***************************************************************
 * hare/esp_bt_main.h some convenience helper for esp_bt_main.h
 *
 * see
 * https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/bluetooth/esp_bt_main.html
 * https://github.com/espressif/esp-idf/blob/639e7ad/components/bt/host/bluedroid/api/include/api/esp_bt_main.h	
 *
 * @author Hannes Reisinger github@HaRe.at
 ***************************************************************/

namespace hare {
  inline const char* to_sz(const esp_bluedroid_status_t status) {
    switch (status) {
      case ESP_BLUEDROID_STATUS_UNINITIALIZED:
        return "ESP_BLUEDROID_STATUS_UNINITIALIZED";
      case ESP_BLUEDROID_STATUS_INITIALIZED:
        return "ESP_BLUEDROID_STATUS_INITIALIZED";
      case ESP_BLUEDROID_STATUS_ENABLED:
        return "ESP_BLUEDROID_STATUS_ENABLED";
      default:
        return "unknown";
    }
  }

  inline void initBluetooth() {
    // https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/error-handling.html
    ESP_ERROR_CHECK(btStart() ? ESP_OK : ESP_FAIL);
    ESP_ERROR_CHECK(esp_bluedroid_init());
	ESP_ERROR_CHECK(esp_bluedroid_enable());
  }
}	// namespache hare

#endif	// HARE_ESP_BT_MAIN_H
