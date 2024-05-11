#include <Arduino.h>

#define potPin 35
//const int pot[] = {34, , , , };
uint8_t potValues[5] = {100, 100, 100, 100, 100};

void potInit() {
  /*
  for (int i = 0; i < 5; i++)
    pinMode(pot[i], INPUT);
    */

  pinMode(potPin, INPUT);
}

void readValues() {
  /*
  for (int i = 0; i < 5; i++)
    potValues[i] = 100 - (int) ((analogRead(pot[i]) * 100) / 4095);
    */

  potValues[0] = 100 - (int) ((analogRead(potPin) * 100) / 4095);
}

void sendValues() {
  for (int i = 0; i < 5; i++)
    Serial.write(potValues[i]);

  Serial.println();
}

void setup() {
  Serial.begin(9600);
  potInit();
}

void loop() {
    readValues();
    sendValues();
}
