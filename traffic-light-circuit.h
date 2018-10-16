#ifndef __TRAFFIC_LIGHT_CIRCUIT_H__
#define __TRAFFIC_LIGHT_CIRCUIT_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct light {
  int red;
  int amber;
  int green;
} TrafficLightPins;

typedef struct trafficLightCircuitEnvironment {
  int high;
  int low;
  int output;
  void (*dWrite)(uint8_t pin, uint8_t value);
  void (*pMode)(uint8_t pin, uint8_t mode);
  TrafficLightPins trafficLightA; 
  TrafficLightPins trafficLightB;
} TrafficLightCircuitEnvironment;

void setTrafficLightCircuitEnvironment(TrafficLightCircuitEnvironment env);
void trafficLightCircuitInitializePins(void); 
void safeSetLights(int valueA, int valueB);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
