
#ifdef HAL_SERVO
#define HAL_SERVO

#include "main.h"
#include "stm32f1xx_hal.h"

/************** KHAI BAO HAM **********/
void Servo_write(int);
void Servo_sweep(int, int);
int map(int goc1, int goc2, int pwm1, int pwm2, int value);
#endif
