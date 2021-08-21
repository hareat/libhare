#ifndef HARE_WIFI_H
#define HARE_WIFI_H

#if defined(ESP8266)
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif

/***************************************************************
 * hare/WiFi.h some convenience helper for WiFi.h
 *
 * @author Hannes Reisinger github@HaRe.at
 ***************************************************************/

#include <hare/esp_log.h>	// ESP_LOG*

namespace hare {
	// hectic blinking is only possible if in setup()
	// pinMode(LED_BUILTIN, OUTPUT);
	inline void setupWiFiSTA(const char* ssid, const char* password) {
		ESP_LOGV(__func__, "begin");
		WiFi.mode(WIFI_STA);
		WiFi.begin(ssid, password);

		// try to connect for 60 seconds - otherwise reboot
		for (unsigned int c = 0; c < 600 && WiFi.status() != WL_CONNECTED; ++c) {
			if (c % 50 == 0) {
				ESP_LOGD(__func__, "connecting to '%s'", ssid);
			}
#ifdef LED_BUILTIN
			// hectic blinking
			delay(50);   // milliseconds
			digitalWrite(LED_BUILTIN, LOW);   // turn the LED on
			delay(50);   // milliseconds
			digitalWrite(LED_BUILTIN, HIGH);  // turn the LED off
#else	// LED_BUILTIN
			delay(100);  // milliseconds
#endif	// LED_BUILTIN
		}

		if (WiFi.status() == WL_CONNECTED) {
			ESP_LOGI(__func__, "WiFi-Station with IP Adresse %s", WiFi.localIP().toString().c_str());
		} else {
			ESP_LOGE(__func__, "restart");
			ESP.restart();
		}
	}


	inline void syncNTP() {
		// TZ Europe/Vienna
		const int gmtOffset = 3600, daylightOffset = 0;	// seconds
		ESP_LOGV(__func__, "gmtOffset_sec=%d, daylightOffset_sec=%d", gmtOffset, daylightOffset);
		// does not work with several server (should work with up to 3)
		// e.g. 192.168.0.1 and only if this is not working with "at.pool.ntp.org"
		// configTime(gmtOffset, daylightOffset, "192.168.0.1", "at.pool.ntp.org");
		configTime(gmtOffset, daylightOffset, "at.pool.ntp.org");
	}
}	// namespace hare

#endif	// HARE_WIFI_H
