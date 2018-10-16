#include <stdint.h>
#include "traffic-light-circuit.h"
#include "util.h"

TrafficLightCircuitEnvironment g_env = { 
  1, 0, 2, 
  (void *)&noop, 
  (void *)&noop, 
  { 1, 2, 3 }, 
  { 1, 2, 3 } 
};

void setTrafficLightCircuitEnvironment(TrafficLightCircuitEnvironment env) {
  g_env = env;
}

void trafficLightCircuitInitializePins(void) {
  g_env.pMode(g_env.trafficLightA.red, g_env.output);
  g_env.pMode(g_env.trafficLightA.amber, g_env.output);
  g_env.pMode(g_env.trafficLightA.green, g_env.output);
  g_env.pMode(g_env.trafficLightB.red, g_env.output);
  g_env.pMode(g_env.trafficLightB.amber, g_env.output);
  g_env.pMode(g_env.trafficLightB.green, g_env.output);
}

/**
 * light:  is the TrafficLight
 * value: 1/2/3 1 = red, 2 = amber, 3 = green red is default
 */
void setLight(TrafficLightPins *light, int value) {
  switch (value) {
  case 0:
    g_env.dWrite(light->red, g_env.low);
    g_env.dWrite(light->amber, g_env.low);
    g_env.dWrite(light->green, g_env.low);
    break;
  case 2:
    g_env.dWrite(light->red, g_env.low);
    g_env.dWrite(light->amber, g_env.high);
    g_env.dWrite(light->green, g_env.low);
    break;
  case 3:
    g_env.dWrite(light->red, g_env.low);
    g_env.dWrite(light->amber, g_env.low);
    g_env.dWrite(light->green, g_env.high);
    break;
  default:
    g_env.dWrite(light->red, g_env.high);
    g_env.dWrite(light->amber, g_env.low);
    g_env.dWrite(light->green, g_env.low);
    break;
  }
}

void safeSetLights(int valA, int valB) {
  if ((valA == 3 && valB == 3) || 
      (valA == 3 && valB == 2) ||
      (valA == 3 && valB == 0) ||
      (valA == 2 && valB == 3) ||
      (valA == 2 && valB == 2) ||
      (valA == 2 && valB == 0) ||
      (valA == 0 && valB == 3) ||
      (valA == 0 && valB == 2) ||
      (valA == 0 && valB == 0)) {
    valA = 1;
    valB = 1;
  }

  setLight(&g_env.trafficLightA, valA);
  setLight(&g_env.trafficLightB, valB);
}
