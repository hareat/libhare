#ifndef HARE_ESP_MAC_TO_SZ_H
#define HARE_ESP_MAC_TO_SZ_H

/********************************************************************
 * hare/mac_sz.h converts a MAC address to a character buffer
 * and vice versa.
 *
 * @author Hannes Reisinger github@HaRe.at
 ********************************************************************/

#define MAC_ADDR_LENGTH 6

#include <stdio.h>	// snprintf sscanf

namespace hare {
  inline const char* mac_to_sz(const uint8_t *mac, char *ach, size_t size) {
    ::snprintf(ach, size, "%02X:%02X:%02X:%02X:%02X:%02X", (int) mac[0], (int) mac[1], (int) mac[2], (int) mac[3], (int) mac[4], (int) mac[5]);
    return ach;
  }

  template<size_t size>
  const char* mac_to_sz(const uint8_t *mac, char (&ach)[size]) {
    return mac_to_sz(mac, ach, size);
  }

  // take care, this uses a static buffer
  inline const char* mac_to_sz(const uint8_t *mac) {
    static char ach[MAC_ADDR_LENGTH * 3];
    return mac_to_sz(mac, ach);
  }


  // @return The number of numbers successfully matched and assigned or EOF.
  //         So only a return value of MAC_ADDR_LENGTH (6) indicates success.
  inline int mac_from_sz(uint8_t *mac, const char *sz) {
    return sscanf(sz, "%2hhx:%2hhx:%2hhx:%2hhx:%2hhx:%2hhx", mac, mac + 1, mac + 2, mac + 3, mac + 4, mac + 5);
  }
}  // namespace hare

#endif  // HARE_ESP_MAC_TO_SZ_H
