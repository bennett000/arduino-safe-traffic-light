#ifndef __SAFE_TRAFFIC_LIGHT_H__
#define __SAFE_TRAFFIC_LIGHT_H__

#ifdef __cplusplus
extern "C" {
#endif


typedef struct arduinoEnvironment {
  int high;
  int low;
  int output;
  void (*dWrite)(uint8_t pin, uint8_t output); 
  void (*pMode)(uint8_t pin, uint8_t mode); 
  void (*delayMs)(int ms); 
  int input;
  void (*delayUs)(int us);
  long (*plsIn)(int pin, int mode);
  void (*printBt)(const char message[]);
  void (*printBtInt)(const int message);
} ArduinoEnvironment;

void mainSetup(ArduinoEnvironment arduinoEnv);
void mainLoop(void);

#ifdef __cplusplus
} // extern "C"
#endif

#endif