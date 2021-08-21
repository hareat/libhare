#ifndef HARE_ESP_PRINT_HEADER_H
#define HARE_ESP_PRINT_HEADER_H

/********************************************************************
 * hare/esp_print_header.h prints a header for starting ESP sketches.
 * Useful if you wonder several years later which sketch is on that
 * ESP you lastly found in a dark corner of your hardware box.
 *
 * @author Hannes Reisinger github@HaRe.at
 ********************************************************************/

#include <string.h>

namespace hare {
  // Prints one line for indication of the sketch on an ESP.
  // Best done directly after setting the baud rate.
  // @param name  The name of the sketch
  inline void printHeader(const char *name) {
    Serial.println();  // because 8266 prints random characters at startup
    Serial.print(name);
    Serial.print(" (compiled on ");
    Serial.print(__DATE__);
    Serial.print(" at ");
    Serial.print(__TIME__);
    Serial.println(")");
  }


  // Prints one line for indication of the sketch on an ESP.
  // Best done directly after setting the baud rate.
  // @param file       __FILE__ at the caller side
  // @param separator  '\\' if you are developing on windows systems
  inline void printHeaderByFile(const char *file, const char separator = '/') {
    char *filename = strrchr(file, separator);
    if (filename) {
      ++filename;  // skip separator
      char *extension = strrchr(filename, '.');
      const int NAME_SIZE = 99;
      if (extension) {
        const size_t length = extension - filename;
        if (length >= NAME_SIZE) {
          // the buffer would be to small
          printHeader(filename);
        } else {
          char name[NAME_SIZE];
          strncpy(name, filename, length);
          name[length] = '\0';
          printHeader(name);
        }
      } else {
        printHeader(filename);
      }
    } else {
      printHeader(file);
    }
  }


  // To avoid different baud rates I prefer using always this setup.
  // @param file       __FILE__ at the caller side
  // @param separator  '\\' if you are developing on windows systems
  inline void setup(const char *file, const char separator = '/') {
    Serial.begin(115200);
    delay(500);  // because 8266 swallows characters otherwise
    printHeaderByFile(file, separator);
  }
}  // namespace hare

#endif  // HARE_ESP_PRINT_HEADER_H
