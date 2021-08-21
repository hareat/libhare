#ifndef HARE_SIMPLE_DHT_H
#define HARE_SIMPLE_DHT_H

#include <SimpleDHT.h>

/*******************************************************************
 * hare/SimpleDHT.h some convenience helper for SimpleDHT.h
 *
 * see
 * <sketchbook location>/libraries/SimpleDHT/SimpleDHT.{h,cpp}
 *
 * @author Hannes Reisinger github@HaRe.at
 *******************************************************************/

namespace hare {
  inline char* getDhtErrorMsg(const int iError, char *achError, const size_t buffer_length) {
    const int t = (iError >> 8), code = (iError & 0xff);
    switch (code) {
      case SimpleDHTErrSuccess:
        snprintf(achError, buffer_length, "'%s' 0x%X (0x%X, 0x%X)", "success", iError, t, code);
        break;
      case SimpleDHTErrStartLow:
        snprintf(achError, buffer_length, "'%s' 0x%X (0x%X, 0x%X)", "start low", iError, t, code);
        break;
      case SimpleDHTErrStartHigh:
        snprintf(achError, buffer_length, "'%s' 0x%X (0x%X, 0x%X)", "start high", iError, t, code);
        break;
      case SimpleDHTErrDataLow:
        snprintf(achError, buffer_length, "'%s' 0x%X (0x%X, 0x%X)", "data low", iError, t, code);
        break;
      case SimpleDHTErrDataRead:
        snprintf(achError, buffer_length, "'%s' 0x%X (0x%X, 0x%X)", "data read", iError, t, code);
        break;
      case SimpleDHTErrDataEOF:
        snprintf(achError, buffer_length, "'%s' 0x%X (0x%X, 0x%X)", "data EOF", iError, t, code);
        break;
      case SimpleDHTErrDataChecksum:
        snprintf(achError, buffer_length, "'%s' 0x%X (0x%X, 0x%X)", "data checksum", iError, t, code);
        break;
      case SimpleDHTErrZeroSamples:
        snprintf(achError, buffer_length, "'%s' 0x%X (0x%X, 0x%X)", "zero samples", iError, t, code);
        break;
      case SimpleDHTErrNoPin:
        snprintf(achError, buffer_length, "'%s' 0x%X (0x%X, 0x%X)", "no pin", iError, t, code);
        break;
      default:
        snprintf(achError, buffer_length, "'%s' 0x%X (0x%X, 0x%X)", "unknown", iError, t, code);
        break;
    }
    return achError;
  }

  template<size_t size>
  char* getDhtErrorMsg(const int iError, char (&ach)[size]) {
    return getDhtErrorMsg(iError, ach, size);
  }

  // take care, this uses a static buffer
  inline char* getDhtErrorMsg(const int iError) {
    static char achError[44];
    return getDhtErrorMsg(iError, achError);
  }
}	// namespace hare

#endif	// HARE_SIMPLE_DHT_H
