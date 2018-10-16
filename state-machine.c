#include "state-machine.h"

const SafeLightState lightStatesSimple[] = {
  { RED, RED, 500, 1 },
  { GREEN, RED, 5000, 2 },
  { AMBER, RED, 1000, 3 },
  { RED, RED, 500, 4 },
  { RED, GREEN, 5000, 5 },
  { RED, AMBER, 1000, 0 }
};

const SafeLightState lightStatesAdvanceA[] = {
  { RED, RED, 500, 1 },
  { ADVANCE, RED, 5000, 2 },
  { GREEN, RED, 5000, 3 },
  { AMBER, RED, 1000, 4 },
  { RED, RED, 500, 5 },
  { RED, GREEN, 5000, 6 },
  { RED, AMBER, 1000, 0 }
};

const SafeLightState lightStatesAdvanceB[] = {
  { RED, RED, 500, 1 },
  { GREEN, RED, 5000, 2 },
  { AMBER, RED, 1000, 3 },
  { RED, RED, 500, 4 },
  { RED, ADVANCE, 5000, 5 },
  { RED, GREEN, 5000, 6 },
  { RED, AMBER, 1000, 0 }
};

const SafeLightState lightStatesAdvanceAB[] = {
  { RED, RED, 500, 1 },
  { ADVANCE, RED, 5000, 2 },
  { GREEN, RED, 5000, 3 },
  { AMBER, RED, 1000, 4 },
  { RED, RED, 500, 5 },
  { RED, ADVANCE, 5000, 6 },
  { RED, GREEN, 5000, 7 },
  { RED, AMBER, 1000, 0 }
};

int g_state = 0;
int g_mode = SIMPLE;

int setMode(LightStateMode newMode) {
  g_mode = newMode;
  g_state = 0;

  return g_mode;
}

SafeLightState getCurrentState(const SafeLightState lightStates[], const int max, int currentStateIndex) {
  if (currentStateIndex >= max) {
    currentStateIndex = 0;
  }
  return lightStates[currentStateIndex];
}

SafeLightState currentState(void) {
  SafeLightState state;
  switch (g_mode) {
    case ADVANCE_A:
      state = getCurrentState(lightStatesAdvanceA, sizeof(lightStatesAdvanceA), g_state);
    break;
    case ADVANCE_B:
      state = getCurrentState(lightStatesAdvanceB, sizeof(lightStatesAdvanceB), g_state);
    break;
    case ADVANCE_AB:
      state = getCurrentState(lightStatesAdvanceAB, sizeof(lightStatesAdvanceAB), g_state);
    break;
    default: // simple
      state = getCurrentState(lightStatesSimple, sizeof(lightStatesSimple), g_state);
    break;
  }
  return state;
}

SafeLightState getNextState(const SafeLightState lightStates[], const int max, int currentStateIndex) {
  if (currentStateIndex >= max) {
    currentStateIndex = 0;
  }
  return lightStates[currentStateIndex];
}

SafeLightState nextState() {
  SafeLightState nextState;
  switch (g_mode) {
    case ADVANCE_A:
      nextState = getNextState(lightStatesAdvanceA, sizeof(lightStatesAdvanceA), g_state);
    break;
    case ADVANCE_B:
      nextState = getNextState(lightStatesAdvanceB, sizeof(lightStatesAdvanceB), g_state);
    break;
    case ADVANCE_AB:
      nextState = getNextState(lightStatesAdvanceAB, sizeof(lightStatesAdvanceAB), g_state);
    break;
    default: // simple
      nextState = getNextState(lightStatesSimple, sizeof(lightStatesSimple), g_state);
    break;
  }
  g_state = nextState.next;
  return nextState;
}
