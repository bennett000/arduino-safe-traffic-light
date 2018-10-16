#include <stdint.h>
#include "safe-traffic-light.h"
#include "state-machine.h"
#include "traffic-light-circuit.h"
#include "util.h"

ArduinoEnvironment arduinoEnv = {
  1,
  0,
  2,
  (void *)&noop,
  (void *)&noop,
  (void *)&noop,
};

int flashDelay = 300;
int flashesRemaining = 0;
const int flashMax = 10;

int mapState(int state) {
  switch (state) {
    case ADVANCE:
      return 3;
    case RED:
      return 1;
    case AMBER:
      return 2;
    case GREEN:
      return 3;
    default:
      return 1;
  }
}

void light(SafeLightState state) {
  safeSetLights(mapState(state.a), mapState(state.b));
}

void mainSetup(ArduinoEnvironment env)
{
  arduinoEnv = env;

  arduinoEnv.pMode(9, arduinoEnv.output);
  arduinoEnv.pMode(10, arduinoEnv.input); 

  TrafficLightCircuitEnvironment tlcEnv = {
    arduinoEnv.high,
    arduinoEnv.low,
    arduinoEnv.output,
    arduinoEnv.dWrite,
    arduinoEnv.pMode,
    {
        8, 7, 6,
    },
    {
        5, 4, 3,
    }
  };
  setTrafficLightCircuitEnvironment(tlcEnv);

  arduinoEnv.printBt("Connected to Safe Traffic Light");
  // Setup the Bluetooth
  // pinMode(BT13, OUTPUT);            // Output LED Flashes for Debugging
  // Serial.begin(9600);               // Set's up Serial Communication at certain speed.
  // Genotronex.begin(9600);           // Serial mapper
  // Genotronex.println("Connected to Safe Traffic Light");

  // Setup the traffic lights
  trafficLightCircuitInitializePins();

  // setMode(ADVANCE_A);
  setMode(SIMPLE);
  // Set the initial state
  SafeLightState state = currentState();
  light(state);
  flashesRemaining = 0;
}

int pingSonar()
{
  long duration = 0;
  arduinoEnv.dWrite(9, arduinoEnv.low);
  arduinoEnv.delayUs(2);

  arduinoEnv.dWrite(9, arduinoEnv.high);
  arduinoEnv.delayUs(10);
  arduinoEnv.dWrite(9, arduinoEnv.low);
  duration = arduinoEnv.plsIn(10, arduinoEnv.high);

  // Calculating the distance
  return duration * 0.034 / 2;
}

int flashState(void) {
  return flashesRemaining % 2 == 0 ? 0 : 3;
}

int loopSolidLights(void) {
    int flashes = 0;
    SafeLightState state = currentState();
    light(state);
    if (state.a == ADVANCE || state.b == ADVANCE) { flashes = flashMax;
    } else {
      nextState();
      arduinoEnv.delayMs(state.delay);
    }
    return flashes;
}

int loopFlashingLights(int remaining) {
    SafeLightState state = currentState();

    if (state.a == ADVANCE) {
      safeSetLights(flashState(), mapState(state.b));
    } else {
      safeSetLights(mapState(state.a), flashState());
    }
    remaining -= 1;
    if (flashesRemaining == 0) {
      nextState();
    }
    arduinoEnv.delayMs(flashDelay);

    return remaining;
}

// The Main Loop Function
void mainLoop(void) {
  int distance = pingSonar();

  arduinoEnv.printBt("D: ");
  arduinoEnv.printBtInt(distance);
  if (flashesRemaining <= 0) {
    flashesRemaining = loopSolidLights();
  } else {
    flashesRemaining = loopFlashingLights(flashesRemaining);
  }
}
