#ifndef __STATE_MACHINE_H__
#define __STATE_MACHINE_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef enum { RED, AMBER, GREEN } LightStateSimple;
typedef enum { RED_A = RED, AMBER_A = AMBER, GREEN_A = GREEN, ADVANCE } LightStateAdvance;
typedef enum { SIMPLE, ADVANCE_A, ADVANCE_AB, ADVANCE_B } LightStateMode;

typedef struct safeLightState {
  int a;
  int b;
  int delay;
  int next;
} SafeLightState;

int setMode(LightStateMode newMode);
SafeLightState nextState(void);
SafeLightState currentState(void);

#ifdef __cplusplus
} // extern "C"
#endif

#endif