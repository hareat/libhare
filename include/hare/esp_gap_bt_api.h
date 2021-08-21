#ifndef HARE_ESP_GAP_BT_API_H
#define HARE_ESP_GAP_BT_API_H

#include <esp_gap_bt_api.h>

/********************************************************************
 * hare/esp_gap_bt_api.h some convenience helper for esp_gap_bt_api.h
 *
 * see
 * https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/bluetooth/esp_gap_bt.html
 * https://github.com/espressif/esp-idf/blob/639e7ad/components/bt/host/bluedroid/api/include/api/esp_gap_bt_api.h
 *
 * @author Hannes Reisinger github@HaRe.at
 ********************************************************************/

#include <string>

namespace hare {
  inline const char* to_sz(const esp_bt_cod_mode_t mode) {
    switch (mode) {
      case ESP_BT_SET_COD_MAJOR_MINOR:
        return "ESP_BT_SET_COD_MAJOR_MINOR";
      case ESP_BT_SET_COD_SERVICE_CLASS:
        return "ESP_BT_SET_COD_SERVICE_CLASS";
      case ESP_BT_CLR_COD_SERVICE_CLASS:
        return "ESP_BT_CLR_COD_SERVICE_CLASS";
      case ESP_BT_SET_COD_ALL:
        return "ESP_BT_SET_COD_ALL";
      case ESP_BT_INIT_COD:
        return "ESP_BT_INIT_COD";
      default:
        return "unknown";
    }
  }

  /*inline const char* to_sz(const esp_bt_connection_mode_t mode) {
    switch (mode) {
      case ESP_BT_NON_CONNECTABLE:
        return "ESP_BT_NON_CONNECTABLE";
      case ESP_BT_CONNECTABLE:
        return "ESP_BT_CONNECTABLE";
      default:
        return "unknown";
    }
  }*/

  /*inline const char* to_sz(const esp_bt_discovery_mode_t mode) {
    switch (mode) {
      case ESP_BT_NON_DISCOVERABLE:
        return "ESP_BT_NON_DISCOVERABLE";
      case ESP_BT_LIMITED_DISCOVERABLE:
        return "ESP_BT_LIMITED_DISCOVERABLE";
      case ESP_BT_GENERAL_DISCOVERABLE:
        return "ESP_BT_GENERAL_DISCOVERABLE";
      default:
        return "unknown";
    }
  }*/

  inline const char* to_sz(const esp_bt_gap_dev_prop_type_t type) {
    switch (type) {
      case ESP_BT_GAP_DEV_PROP_BDNAME:
        return "ESP_BT_GAP_DEV_PROP_BDNAME";
      case ESP_BT_GAP_DEV_PROP_COD:
        return "ESP_BT_GAP_DEV_PROP_COD";
      case ESP_BT_GAP_DEV_PROP_RSSI:
        return "ESP_BT_GAP_DEV_PROP_RSSI";
      case ESP_BT_GAP_DEV_PROP_EIR:
        return "ESP_BT_GAP_DEV_PROP_EIR";
      default:
        return "unknown";
    }
  }

  inline std::string to_str(const esp_bt_cod_srvc_t srvc) {
    if (srvc == ESP_BT_COD_SRVC_NONE)
      return "ESP_BT_COD_SRVC_NONE";

    std::string result = "ESP_BT_COD_SRVC_";
    if (srvc & ESP_BT_COD_SRVC_LMTD_DISCOVER)
        result += "LMTD_DISCOVER|";
    if (srvc & ESP_BT_COD_SRVC_POSITIONING)
        result += "POSITIONING|";
    if (srvc & ESP_BT_COD_SRVC_NETWORKING)
        result += "NETWORKING|";
    if (srvc & ESP_BT_COD_SRVC_RENDERING)
        result += "RENDERING|";
    if (srvc & ESP_BT_COD_SRVC_CAPTURING)
        result += "CAPTURING|";
    if (srvc & ESP_BT_COD_SRVC_OBJ_TRANSFER)
        result += "OBJ_TRANSFER|";
    if (srvc & ESP_BT_COD_SRVC_AUDIO)
        result += "AUDIO|";
    if (srvc & ESP_BT_COD_SRVC_TELEPHONY)
        result += "TELEPHONY|";
    if (srvc & ESP_BT_COD_SRVC_INFORMATION)
        result += "INFORMATION|";
    result.resize(result.size() - 1);	// remove last '|'
    return result;
  }

  inline const char* to_sz(const esp_bt_pin_type_t type) {
    switch (type) {
      case ESP_BT_PIN_TYPE_VARIABLE:
        return "ESP_BT_PIN_TYPE_VARIABLE";
      case ESP_BT_PIN_TYPE_FIXED:
        return "ESP_BT_PIN_TYPE_FIXED";
      default:
        return "unknown";
    }
  }

  inline const char* to_sz(const esp_bt_sp_param_t param) {
    switch (param) {
      case ESP_BT_SP_IOCAP_MODE:
        return "ESP_BT_SP_IOCAP_MODE";
      default:
        return "unknown";
    }
  }

  inline const char* to_sz(const esp_bt_cod_major_dev_t dev) {
    switch (dev) {
      case ESP_BT_COD_MAJOR_DEV_MISC:
        return "ESP_BT_COD_MAJOR_DEV_MISC";
      case ESP_BT_COD_MAJOR_DEV_COMPUTER:
        return "ESP_BT_COD_MAJOR_DEV_COMPUTER";
      case ESP_BT_COD_MAJOR_DEV_PHONE:
        return "ESP_BT_COD_MAJOR_DEV_PHONE";
      case ESP_BT_COD_MAJOR_DEV_LAN_NAP:
        return "ESP_BT_COD_MAJOR_DEV_LAN_NAP";
      case ESP_BT_COD_MAJOR_DEV_AV:
        return "ESP_BT_COD_MAJOR_DEV_AV";
      case ESP_BT_COD_MAJOR_DEV_PERIPHERAL:
        return "ESP_BT_COD_MAJOR_DEV_PERIPHERAL";
      case ESP_BT_COD_MAJOR_DEV_IMAGING:
        return "ESP_BT_COD_MAJOR_DEV_IMAGING";
      case ESP_BT_COD_MAJOR_DEV_WEARABLE:
        return "ESP_BT_COD_MAJOR_DEV_WEARABLE";
      case ESP_BT_COD_MAJOR_DEV_TOY:
        return "ESP_BT_COD_MAJOR_DEV_TOY";
      case ESP_BT_COD_MAJOR_DEV_HEALTH:
        return "ESP_BT_COD_MAJOR_DEV_HEALTH";
      case ESP_BT_COD_MAJOR_DEV_UNCATEGORIZED:
        return "ESP_BT_COD_MAJOR_DEV_UNCATEGORIZED";
      default:
        return "unknown";
    }
  }

  inline const char* to_sz(const esp_bt_gap_discovery_state_t state) {
    switch (state) {
      case ESP_BT_GAP_DISCOVERY_STOPPED:
        return "ESP_BT_GAP_DISCOVERY_STOPPED";
      case ESP_BT_GAP_DISCOVERY_STARTED:
        return "ESP_BT_GAP_DISCOVERY_STARTED";
      default:
        return "unknown";
    }
  }

  inline const char* to_sz(const esp_bt_gap_cb_event_t event) {
    switch (event) {
      case ESP_BT_GAP_DISC_RES_EVT:
        return "ESP_BT_GAP_DISC_RES_EVT";
      case ESP_BT_GAP_DISC_STATE_CHANGED_EVT:
        return "ESP_BT_GAP_DISC_STATE_CHANGED_EVT";
      case ESP_BT_GAP_RMT_SRVCS_EVT:
        return "ESP_BT_GAP_RMT_SRVCS_EVT";
      case ESP_BT_GAP_RMT_SRVC_REC_EVT:
        return "ESP_BT_GAP_RMT_SRVC_REC_EVT";
      case ESP_BT_GAP_AUTH_CMPL_EVT:
        return "ESP_BT_GAP_AUTH_CMPL_EVT";
      case ESP_BT_GAP_PIN_REQ_EVT:
        return "ESP_BT_GAP_PIN_REQ_EVT";
      case ESP_BT_GAP_CFM_REQ_EVT:
        return "ESP_BT_GAP_CFM_REQ_EVT";
      case ESP_BT_GAP_KEY_NOTIF_EVT:
        return "ESP_BT_GAP_KEY_NOTIF_EVT";
      case ESP_BT_GAP_KEY_REQ_EVT:
        return "ESP_BT_GAP_KEY_REQ_EVT";
      case ESP_BT_GAP_READ_RSSI_DELTA_EVT:
        return "ESP_BT_GAP_READ_RSSI_DELTA_EVT";
      //case ESP_BT_GAP_CONFIG_EIR_DATA_EVT:
      //  return "ESP_BT_GAP_CONFIG_EIR_DATA_EVT";
      //case ESP_BT_GAP_SET_AFH_CHANNELS_EVT:
      //  return "ESP_BT_GAP_SET_AFH_CHANNELS_EVT";
      //case ESP_BT_GAP_READ_REMOTE_NAME_EVT:
      //  return "ESP_BT_GAP_READ_REMOTE_NAME_EVT";
      //case ESP_BT_GAP_MODE_CHG_EVT:
      //  return "ESP_BT_GAP_MODE_CHG_EVT";
      case ESP_BT_GAP_REMOVE_BOND_DEV_COMPLETE_EVT:
        return "ESP_BT_GAP_REMOVE_BOND_DEV_COMPLETE_EVT";
      //case ESP_BT_GAP_QOS_CMPL_EVT:
      //  return "ESP_BT_GAP_QOS_CMPL_EVT";
      case ESP_BT_GAP_EVT_MAX:
        return "ESP_BT_GAP_EVT_MAX";
      default:
        return "unknown";
    }
  }

  inline const char* to_sz(const esp_bt_inq_mode_t mode) {
    switch (mode) {
      case ESP_BT_INQ_MODE_GENERAL_INQUIRY:
        return "ESP_BT_INQ_MODE_GENERAL_INQUIRY";
      case ESP_BT_INQ_MODE_LIMITED_INQUIRY:
        return "ESP_BT_INQ_MODE_LIMITED_INQUIRY";
      default:
        return "unknown";
    }
  }
}  // namespace hare

#endif  // HARE_ESP_GAP_BT_API_H
