#ifndef HARE_ESP_PINAUTORESTORE_H
#define HARE_ESP_PINAUTORESTORE_H

/********************************************************************
 * hare/esp_pinautorestore.h changes and restores the LOW/HIGH state
 * of a PIN.
 *
 * @author Hannes Reisinger github@HaRe.at
 ********************************************************************/

/***************************************************************
 * hare_lED.h Hilfsklasse fuer das Ein-/Ausschalten der LED
 ***************************************************************/

namespace hare {
  template <int PIN>
  struct PinAutoRestore {
    const int old_value;
    PinAutoRestore<PIN>() : old_value(digitalRead()) {
      digitalWrite(PIN, !old_value);
    }
    ~PinAutoRestore<PIN>() {
      digitalWrite(PIN, old_value);
    }
  };
}	// namespache hare

#endif  // HARE_ESP_PINAUTORESTORE_H
