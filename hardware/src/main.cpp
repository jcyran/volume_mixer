#include <avr/io.h>
#include <util/delay.h>
#include "libADC.h"
#include "libUART.h"

ADCHandler adc;
USARTHandler usart;
uint8_t pot[5] = { A0, A1, A2, A3, A4 };
uint8_t potValues[5];


void readValues(void);
void sendValues(void);


int main() {
  adc.init();
  usart.init(9600);

  while(true) {
    readValues();
    sendValues();
    
    _delay_ms(500);
  }

  return 0;
}


void readValues(void) {
  for (int i = 0; i < 5; i++)
    potValues[i] = 100 - (int) ((adc.convert(pot[i]) * 100) / 4095);
}

void sendValues(void) {
  for (int i = 0; i < 5; i++)
    usart.sendByte(potValues[i]);

  usart.sendByte('\n');
}