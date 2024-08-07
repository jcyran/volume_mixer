#include "libADC.h"

uint16_t ADCConversion(int analogIO) {
    ADMUX |= analogIO;
    ADCSRA |= (1 << ADSC);
    
    while (ADCSRA & (1 << ADSC));

    return ADC;
}