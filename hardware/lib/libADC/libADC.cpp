#include "libADC.h"

void ADCHandler::init(void) {
  ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

  ADMUX = (1 << REFS0);
}

uint16_t ADCHandler::convert(int analogIO) {
  ADMUX |= analogIO;
  ADCSRA |= (1 << ADSC);
  
  while (ADCSRA & (1 << ADSC));
  ADMUX = (ADMUX>>4)<<4; //reset the 4 least significant bits (channel selection bits)

  return ADC;
}