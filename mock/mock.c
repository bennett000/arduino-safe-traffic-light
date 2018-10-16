#include <stdint.h>
#include <stdio.h>
#include "../safe-traffic-light.h"

void delay(uint8_t time) {
  printf("\n Delay for %dms \n\n", time);
}

void delayMicroseconds(uint8_t time) {
  printf("\n Delay for %dus \n\n", time);
}

void outputLight(char name[], uint8_t value) {
  printf("%s %s\n", name, value == 0 ? "off" : "on");
}

long pulseIn(uint8_t pin, uint8_t mode) {
  printf("Pulse in on pin %d mode %d\n", pin, mode);
  return (long)0.5;
}

void printBt(const char *message) {
  printf("Blue Tooth: %s", message);
}

void printBtInt(const int message) {
  printf("Blue Tooth: %d", message);
}

void digitalWrite(uint8_t pin, uint8_t value) {
  switch (pin) {
    case 8:
      outputLight("A: Red", value);
      break;
    case 7:
      outputLight("A: Amber", value);
      break;
    case 6:
      outputLight("A: Green", value);
      break;
    case 5:
      outputLight("B: Red", value);
      break;
    case 4:
      outputLight("B: Amber", value);
      break;
    case 3:
      outputLight("B: Green", value);
      break;
    default:
      printf("Digital write to unexpected pin: %d", pin);
      break;
  }
}

void pinMode(uint8_t pin, uint8_t mode) {
  printf("Setting pin %d to %d\n", pin, mode);
}


int main(void) {
  int i = 0;
  ArduinoEnvironment env = {
    1, 0, 2,
    &digitalWrite,
    &pinMode,
    &delay,
    3,
    &delayMicroseconds,
    &pulseIn,
    &printBt,
    &printBtInt
  };

  mainSetup(env);

  for (i = 0; i < 300; i += 1) {
    mainLoop();
  }
  return 0;
}
