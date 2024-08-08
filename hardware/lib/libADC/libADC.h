#pragma once

#include <avr/io.h>

#define A0 0
#define A1 1
#define A2 2
#define A3 3
#define A4 4
#define A5 5
#define A6 6
#define A7 7

class ADCHandler {
public:
  void init(void);
  uint16_t convert(int analogIO);
};