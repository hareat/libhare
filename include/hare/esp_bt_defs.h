#ifndef HARE_ESP_BT_DEFS_H
#define HARE_ESP_BT_DEFS_H

#include <esp_bt_defs.h>

/***************************************************************
 * hare/esp_bt_defs.h some convenience helper for esp_bt_defs.h
 *
 * see
 * https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/bluetooth/esp_bt_defs.html
 * https://github.com/espressif/esp-idf/blob/639e7ad/components/bt/host/bluedroid/api/include/api/esp_bt_defs.h
 *
 * @author Hannes Reisinger github@HaRe.at
 ***************************************************************/

#include <hare/mac_sz.h>

#include <string.h>	// memcmp

namespace hare {
  inline const char* to_sz(const esp_bt_status_t status) {
    switch (status) {
      case ESP_BT_STATUS_SUCCESS:
        return "ESP_BT_STATUS_SUCCESS";
      case ESP_BT_STATUS_FAIL:
        return "ESP_BT_STATUS_FAIL";
      case ESP_BT_STATUS_NOT_READY:
        return "ESP_BT_STATUS_NOT_READY";
      case ESP_BT_STATUS_NOMEM:
        return "ESP_BT_STATUS_NOMEM";
      case ESP_BT_STATUS_BUSY:
        return "ESP_BT_STATUS_BUSY";
      case ESP_BT_STATUS_DONE:
        return "ESP_BT_STATUS_DONE";
      case ESP_BT_STATUS_UNSUPPORTED:
        return "ESP_BT_STATUS_UNSUPPORTED";
      case ESP_BT_STATUS_PARM_INVALID:
        return "ESP_BT_STATUS_PARM_INVALID";
      case ESP_BT_STATUS_UNHANDLED:
        return "ESP_BT_STATUS_UNHANDLED";
      case ESP_BT_STATUS_AUTH_FAILURE:
        return "ESP_BT_STATUS_AUTH_FAILURE";
      case ESP_BT_STATUS_RMT_DEV_DOWN:
        return "ESP_BT_STATUS_RMT_DEV_DOWN";
      case ESP_BT_STATUS_AUTH_REJECTED:
        return "ESP_BT_STATUS_AUTH_REJECTED";
      case ESP_BT_STATUS_INVALID_STATIC_RAND_ADDR:
        return "ESP_BT_STATUS_INVALID_STATIC_RAND_ADDR";
      case ESP_BT_STATUS_PENDING:
        return "ESP_BT_STATUS_PENDING";
      case ESP_BT_STATUS_UNACCEPT_CONN_INTERVAL:
        return "ESP_BT_STATUS_UNACCEPT_CONN_INTERVAL";
      case ESP_BT_STATUS_PARAM_OUT_OF_RANGE:
        return "ESP_BT_STATUS_PARAM_OUT_OF_RANGE";
      case ESP_BT_STATUS_TIMEOUT:
        return "ESP_BT_STATUS_TIMEOUT";
      case ESP_BT_STATUS_PEER_LE_DATA_LEN_UNSUPPORTED:
        return "ESP_BT_STATUS_PEER_LE_DATA_LEN_UNSUPPORTED";
      case ESP_BT_STATUS_CONTROL_LE_DATA_LEN_UNSUPPORTED:
        return "ESP_BT_STATUS_CONTROL_LE_DATA_LEN_UNSUPPORTED";
      case ESP_BT_STATUS_ERR_ILLEGAL_PARAMETER_FMT:
        return "ESP_BT_STATUS_ERR_ILLEGAL_PARAMETER_FMT";
      case ESP_BT_STATUS_MEMORY_FULL:
        return "ESP_BT_STATUS_MEMORY_FULL";
      //case ESP_BT_STATUS_EIR_TOO_LARGE:
      //  return "ESP_BT_STATUS_EIR_TOO_LARGE";
      default:
        return "unknown";
    }
  }

  inline const char* to_sz(const esp_bt_dev_type_t type) {
    switch (type) {
      case ESP_BT_DEVICE_TYPE_BREDR:
        return "ESP_BT_DEVICE_TYPE_BREDR";
      case ESP_BT_DEVICE_TYPE_BLE:
        return "ESP_BT_DEVICE_TYPE_BLE";
      case ESP_BT_DEVICE_TYPE_DUMO:
        return "ESP_BT_DEVICE_TYPE_DUMO";
      default:
        return "unknown";
    }
  }

  inline const char* to_sz(const esp_ble_addr_type_t type) {
    switch (type) {
      case BLE_ADDR_TYPE_PUBLIC:
        return "BLE_ADDR_TYPE_PUBLIC";
      case BLE_ADDR_TYPE_RANDOM:
        return "BLE_ADDR_TYPE_RANDOM";
      case BLE_ADDR_TYPE_RPA_PUBLIC:
        return "BLE_ADDR_TYPE_RPA_PUBLIC";
      case BLE_ADDR_TYPE_RPA_RANDOM:
        return "BLE_ADDR_TYPE_RPA_RANDOM";
      default:
        return "unknown";
    }
  }

  /*inline const char* to_sz(const esp_ble_wl_addr_type_t type) {
    switch (type) {
      case BLE_WL_ADDR_TYPE_PUBLIC:
        return "BLE_WL_ADDR_TYPE_PUBLIC";
      case BLE_WL_ADDR_TYPE_RANDOM:
        return "BLE_WL_ADDR_TYPE_RANDOM";
      default:
        return "unknown";
    }
  }*/


  inline const char* to_sz(esp_bd_addr_t bda, char *ach, size_t size) {
    return mac_to_sz(bda, ach, size);
  }

  template<size_t size>
  const char* to_sz(esp_bd_addr_t bda, char (&ach)[size]) {
    return mac_to_sz(bda, ach, size);
  }

  // take care, this uses a static buffer
  inline const char* to_sz(esp_bd_addr_t bda) {
    return mac_to_sz(bda);
  }


  inline void from_sz(esp_bd_addr_t &bda, const char *sz) {
    sscanf(sz, "%02x:%02x:%02x:%02x:%02x:%02x", bda, bda + 1, bda + 2, bda + 3, bda + 4, bda + 5);
  }


  inline bool equals(esp_bd_addr_t left, esp_bd_addr_t right) {
    return left == right || memcmp(left, right, ESP_BD_ADDR_LEN) == 0;
  }
}  // namespace hare

#endif  // HARE_ESP_BT_DEFS_H	
