#include "Servo.h"
void Servo_write(int angle)
{
	/* Tu sua x thanh so timer */
	htim2.Instance->CCR1 = angle; 
}
void Servo_sweep(int goc1, int goc2)
{
	for(int i = goc1; i <= goc2; i++)
		{
			servo_write(i);
			HAL_Delay(10);
		}
		for(int i = goc2; i >= goc1; i--)
		{
			servo_write(i);
			HAL_Delay(10);
		}
}
int map(int goc1, int goc2, int pwm1, int pwm2, int value)
{
	 return (1.0*(value-goc1))/((goc2-goc1)*1.0) * (pwm2-pwm1)+pwm1;
}