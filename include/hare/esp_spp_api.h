#ifndef HARE_ESP_SPP_API_H
#define HARE_ESP_SPP_API_H

#include <esp_spp_api.h>

/***************************************************************
 * hare/esp_spp_api.h some convenience helper for esp_spp_api.h
 *
 * see
 * https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/bluetooth/esp_spp.html
 * https://github.com/espressif/esp-idf/blob/639e7ad/components/bt/host/bluedroid/api/include/api/esp_spp_api.h
 *
 * @author Hannes Reisinger github@HaRe.at
 ***************************************************************/

namespace hare {
  inline const char* to_sz(const esp_spp_status_t status) {
    switch (status) {
      case ESP_SPP_SUCCESS:
        return "ESP_SPP_SUCCESS";
      case ESP_SPP_FAILURE:
        return "ESP_SPP_FAILURE";
      case ESP_SPP_BUSY:
        return "ESP_SPP_BUSY";
      case ESP_SPP_NO_DATA:
        return "ESP_SPP_NO_DATA";
      case ESP_SPP_NO_RESOURCE:
        return "ESP_SPP_NO_RESOURCE";
      case ESP_SPP_NEED_INIT:
        return "ESP_SPP_NEED_INIT";
      case ESP_SPP_NEED_DEINIT:
        return "ESP_SPP_NEED_DEINIT";
      case ESP_SPP_NO_CONNECTION:
        return "ESP_SPP_NO_CONNECTION";
      case ESP_SPP_NO_SERVER:
        return "ESP_SPP_NO_SERVER";
      default:
        return "unknown";
    }
  }

  inline const char* to_sz(const esp_spp_role_t role) {
    switch (role) {
      case ESP_SPP_ROLE_MASTER:
        return "ESP_SPP_ROLE_MASTER";
      case ESP_SPP_ROLE_SLAVE:
        return "ESP_SPP_ROLE_SLAVE";
      default:
        return "unknown";
    }
  }

  inline const char* to_sz(const esp_spp_mode_t mode) {
    switch (mode) {
      case ESP_SPP_MODE_CB:
        return "ESP_SPP_MODE_CB";
      case ESP_SPP_MODE_VFS:
        return "ESP_SPP_MODE_VFS";
      default:
        return "unknown";
    }
  }

  inline const char* to_sz(const esp_spp_cb_event_t event) {
    switch (event) {
      case ESP_SPP_INIT_EVT:
        return "ESP_SPP_INIT_EVT";
      case ESP_SPP_UNINIT_EVT:
        return "ESP_SPP_UNINIT_EVT";
      case ESP_SPP_DISCOVERY_COMP_EVT:
        return "ESP_SPP_DISCOVERY_COMP_EVT";
      case ESP_SPP_OPEN_EVT:
        return "ESP_SPP_OPEN_EVT";
      case ESP_SPP_CLOSE_EVT:
        return "ESP_SPP_CLOSE_EVT";
      case ESP_SPP_START_EVT:
        return "ESP_SPP_START_EVT";
      case ESP_SPP_CL_INIT_EVT:
        return "ESP_SPP_CL_INIT_EVT";
      case ESP_SPP_DATA_IND_EVT:
        return "ESP_SPP_DATA_IND_EVT";
      case ESP_SPP_CONG_EVT:
        return "ESP_SPP_CONG_EVT";
      case ESP_SPP_WRITE_EVT:
        return "ESP_SPP_WRITE_EVT";
      case ESP_SPP_SRV_OPEN_EVT:
        return "ESP_SPP_SRV_OPEN_EVT";
      case ESP_SPP_SRV_STOP_EVT:
        return "ESP_SPP_SRV_STOP_EVT";
      default:
        return "unknown";
    }
  }
}  // namespache hare

#endif  // HARE_ESP_SPP_API_H
