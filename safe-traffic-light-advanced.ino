#include <stddef.h>
#include <SoftwareSerial.h>
#include "safe-traffic-light.h";

SoftwareSerial Genotronex(11, 12);  // RX, TX (Mapped from defaul 0/1)

void printBt(const char message[]) {
  Genotronex.println(message);
}

void printBtInt(const int message) {
  Genotronex.println(message);
}

void delayMs(int ms) {
  delay(ms);
}

void delayUs(int us) {
  delayMicroseconds(us);
}

long plsIn(int pin, int mode) {
  return pulseIn(pin, mode);
}

ArduinoEnvironment env = {
  HIGH,
  LOW,
  OUTPUT,
  &digitalWrite,
  &pinMode,
  &delayMs,
  INPUT,
  &delayUs,
  &plsIn,
  &printBt,
  &printBtInt
};

void setup(void) {
  Serial.begin(9600);
  Genotronex.begin(9600);
  mainSetup(env);
  digitalWrite(8, HIGH);
}

void loop(void) {
  mainLoop();
}
