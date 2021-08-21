#ifndef HARE_ESP_GAP_BLE_API_H
#define HARE_ESP_GAP_BLE_API_H

#include <esp_gap_ble_api.h>

/********************************************************************
 * hare/esp_gap_ble_api.h some convenience helper for esp_gap_bt_api.h
 *
 * see
 * https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/bluetooth/esp_gap_bt.html
 * https://github.com/espressif/esp-idf/blob/639e7ad/components/bt/host/bluedroid/api/include/api/esp_gap_bt_api.h
 *
 * @author Hannes Reisinger github@HaRe.at
 ********************************************************************/

#include <string>

namespace hare {

  inline std::string esp_ble_adv_flag_to_str(const int flag) {
    if (flag == ESP_BLE_ADV_FLAG_NON_LIMIT_DISC)
      return "ESP_BLE_ADV_FLAG_NON_LIMIT_DISC";

    std::string result = "ESP_BLE_ADV_FLAG_";
    if (flag & ESP_BLE_ADV_FLAG_LIMIT_DISC)
        result += "LIMIT_DISC|";
    if (flag & ESP_BLE_ADV_FLAG_GEN_DISC)
        result += "GEN_DISC|";
    if (flag & ESP_BLE_ADV_FLAG_BREDR_NOT_SPT)
        result += "BREDR_NOT_SPT|";
    if (flag & ESP_BLE_ADV_FLAG_DMT_CONTROLLER_SPT)
        result += "DMT_CONTROLLER_SPT|";
    if (flag & ESP_BLE_ADV_FLAG_DMT_HOST_SPT)
        result += "DMT_HOST_SPT|";
    result.resize(result.size() - 1);	// remove last '|'
    return result;
  }

  inline const char* to_sz(const esp_gap_ble_cb_event_t event) {
    switch (event) {
      case ESP_GAP_BLE_ADV_DATA_SET_COMPLETE_EVT:
        return "ESP_GAP_BLE_ADV_DATA_SET_COMPLETE_EVT";
      case ESP_GAP_BLE_SCAN_RSP_DATA_SET_COMPLETE_EVT:
        return "ESP_GAP_BLE_SCAN_RSP_DATA_SET_COMPLETE_EVT";
      case ESP_GAP_BLE_SCAN_PARAM_SET_COMPLETE_EVT:
        return "ESP_GAP_BLE_SCAN_PARAM_SET_COMPLETE_EVT";
      case ESP_GAP_BLE_SCAN_RESULT_EVT:
        return "ESP_GAP_BLE_SCAN_RESULT_EVT";
      case ESP_GAP_BLE_ADV_DATA_RAW_SET_COMPLETE_EVT:
        return "ESP_GAP_BLE_ADV_DATA_RAW_SET_COMPLETE_EVT";
      case ESP_GAP_BLE_SCAN_RSP_DATA_RAW_SET_COMPLETE_EVT:
        return "ESP_GAP_BLE_SCAN_RSP_DATA_RAW_SET_COMPLETE_EVT";
      case ESP_GAP_BLE_ADV_START_COMPLETE_EVT:
        return "ESP_GAP_BLE_ADV_START_COMPLETE_EVT";
      case ESP_GAP_BLE_SCAN_START_COMPLETE_EVT:
        return "ESP_GAP_BLE_SCAN_START_COMPLETE_EVT";
      case ESP_GAP_BLE_AUTH_CMPL_EVT:
        return "ESP_GAP_BLE_AUTH_CMPL_EVT";
      case ESP_GAP_BLE_KEY_EVT:
        return "ESP_GAP_BLE_KEY_EVT";
      case ESP_GAP_BLE_SEC_REQ_EVT:
        return "ESP_GAP_BLE_SEC_REQ_EVT";
      case ESP_GAP_BLE_PASSKEY_NOTIF_EVT:
        return "ESP_GAP_BLE_PASSKEY_NOTIF_EVT";
      case ESP_GAP_BLE_PASSKEY_REQ_EVT:
        return "ESP_GAP_BLE_PASSKEY_REQ_EVT";
      case ESP_GAP_BLE_OOB_REQ_EVT:
        return "ESP_GAP_BLE_OOB_REQ_EVT";
      case ESP_GAP_BLE_LOCAL_IR_EVT:
        return "ESP_GAP_BLE_LOCAL_IR_EVT";
      case ESP_GAP_BLE_LOCAL_ER_EVT:
        return "ESP_GAP_BLE_LOCAL_ER_EVT";
      case ESP_GAP_BLE_NC_REQ_EVT:
        return "ESP_GAP_BLE_NC_REQ_EVT";
      case ESP_GAP_BLE_ADV_STOP_COMPLETE_EVT:
        return "ESP_GAP_BLE_ADV_STOP_COMPLETE_EVT";
      case ESP_GAP_BLE_SCAN_STOP_COMPLETE_EVT:
        return "ESP_GAP_BLE_SCAN_STOP_COMPLETE_EVT";
      case ESP_GAP_BLE_SET_STATIC_RAND_ADDR_EVT:
        return "ESP_GAP_BLE_SET_STATIC_RAND_ADDR_EVT";
      case ESP_GAP_BLE_UPDATE_CONN_PARAMS_EVT:
        return "ESP_GAP_BLE_UPDATE_CONN_PARAMS_EVT";
      case ESP_GAP_BLE_SET_PKT_LENGTH_COMPLETE_EVT:
        return "ESP_GAP_BLE_SET_PKT_LENGTH_COMPLETE_EVT";
      case ESP_GAP_BLE_SET_LOCAL_PRIVACY_COMPLETE_EVT:
        return "ESP_GAP_BLE_SET_LOCAL_PRIVACY_COMPLETE_EVT";
      case ESP_GAP_BLE_REMOVE_BOND_DEV_COMPLETE_EVT:
        return "ESP_GAP_BLE_REMOVE_BOND_DEV_COMPLETE_EVT";
      case ESP_GAP_BLE_CLEAR_BOND_DEV_COMPLETE_EVT:
        return "ESP_GAP_BLE_CLEAR_BOND_DEV_COMPLETE_EVT";
      case ESP_GAP_BLE_GET_BOND_DEV_COMPLETE_EVT:
        return "ESP_GAP_BLE_GET_BOND_DEV_COMPLETE_EVT";
      case ESP_GAP_BLE_READ_RSSI_COMPLETE_EVT:
        return "ESP_GAP_BLE_READ_RSSI_COMPLETE_EVT";
      case ESP_GAP_BLE_UPDATE_WHITELIST_COMPLETE_EVT:
        return "ESP_GAP_BLE_UPDATE_WHITELIST_COMPLETE_EVT";
      case ESP_GAP_BLE_UPDATE_DUPLICATE_EXCEPTIONAL_LIST_COMPLETE_EVT:
        return "ESP_GAP_BLE_UPDATE_DUPLICATE_EXCEPTIONAL_LIST_COMPLETE_EVT";
      default:
        return "unknown";
    }
  }
}  // namespace hare

#endif  // HARE_ESP_GAP_BT_API_H
