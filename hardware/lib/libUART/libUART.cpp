#include "libUART.h"

static bool txBusy;

ISR(USART_TX_vect) {
  txBusy = true;
}

void USARTHandler::init(uint32_t baudrate, bool highspeed) {
  uint8_t speed = 16;

  if (highspeed) {
    UCSR0A |= 1 << U2X0;
    speed = 8;
  }

  baudrate = (F_CPU / baudrate * speed) - 1;

  UBRR0H = (baudrate & 0x0f00) >> 8;
  UBRR0L = baudrate & 0x00ff;

  UCSR0A |= (1 << TXEN0) | (1 << RXEN0);
}

void USARTHandler::sendByte(uint8_t data) {
  while (txBusy);
  txBusy = false;

  UDR0 = data;
}
