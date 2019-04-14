/* IRLibProtocols.cpp
 * Part of IRLib Library for Arduino receiving, decoding, and sending
 * infrared signals. See COPYRIGHT.txt and LICENSE.txt for more information.
 */
/*
 * This module enumerates the various supported protocols and defines a program memory
 * string used by the dump routines or your sketches to display the name of a protocol.
 * It is used by both Send and Decode sections of the code but not Receive.
 */
#include "IRLibProtocols.h"

/*
 * Returns a pointer to a flash stored string that is the name of the protocol received.
 */
const __FlashStringHelper *Pnames(uint8_t type) {
  if(type>89) return F("Unsup");
  if(type>LAST_PROTOCOL) type=UNKNOWN;
  // You can add additional strings before the entry for hash code.
  const __FlashStringHelper* const type0 = F("Unknown");
  const __FlashStringHelper* const type1 = F("NEC");
  const __FlashStringHelper* const type2 = F("Sony");
  const __FlashStringHelper* const type3 = F("RC5");
  const __FlashStringHelper* const type4 = F("RC6");
  const __FlashStringHelper* const type5 = F("Panasonic Old");
  const __FlashStringHelper* const type6 = F("JVC");
  const __FlashStringHelper* const type7 = F("NECx");
  const __FlashStringHelper* const type8 = F("Samsung36");
  const __FlashStringHelper* const type9 = F("G.I.Cable");
  const __FlashStringHelper* const type10 = F("DirecTV");
  const __FlashStringHelper* const type11 = F("rcmm");
  const __FlashStringHelper* const type12 = F("CYKM");
  const __FlashStringHelper *Names[LAST_PROTOCOL+1]={
    type0, type1, type2, type3, type4, type5, type6, type7, type8, type9, type10, type11, type12
	  // F("Unknown"),F("NEC"),F("Sony"),F("RC5"),F("RC6"),F("Panasonic Old"),F("JVC"),
	  // F("NECx"),F("Samsung36"),F("G.I.Cable"),F("DirecTV"),F("rcmm"),F("CYKM")
    // ,F("Additional_13")//expand or edit these
  };
  return Names[type];
};

