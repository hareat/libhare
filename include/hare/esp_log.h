#ifndef HARE_ESP_LOG_H
#define HARE_ESP_LOG_H

/********************************************************************
 * hare/esp_log.h on ESP32 just uses esp_log.h but on ESP8266
 * provides similar alternatives.
 * In Arduino IDE a ESP32 or ESP8266 board must be selected.
 * Then go to the Tools Menu and set the Core Debug Level.
 *
 * @author Hannes Reisinger github@HaRe.at
 ********************************************************************/

#if defined(ESP32)

	#include <esp_log.h>

#elif defined(ESP8266)

	#define DBGLOG_FUNCTION printf
	#include "umm_malloc/dbglog/dbglog.h"
	#define ESP_LOGV(func, format, ...) DBGLOG_TRACE("%c %s() " format "\n", 'V', func, ## __VA_ARGS__)
	#define ESP_LOGD(func, format, ...) DBGLOG_DEBUG("%c %s() " format "\n", 'D', func, ## __VA_ARGS__)
	#define ESP_LOGI(func, format, ...) DBGLOG_INFO("%c %s() " format "\n", 'I', func, ## __VA_ARGS__)
	#define ESP_LOGW(func, format, ...) DBGLOG_WARNING("%c %s() " format "\n", 'W', func, ## __VA_ARGS__)
	#define ESP_LOGE(func, format, ...) DBGLOG_ERROR("%c %s() " format "\n", 'E', func, ## __VA_ARGS__)

#else	// !ESP32 and !ESP8266

	You have to select an ESP32 or ESP8266 board first!

#endif	// ESP32 ESP8266

#endif  // HARE_ESP_LOG_H
