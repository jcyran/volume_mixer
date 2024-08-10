#pragma once

#include <avr/io.h>
#include <avr/interrupt.h>


class USARTHandler {
public:
  void init(uint32_t baudrate, bool highspeed = false);
  void sendByte(uint8_t data);
};