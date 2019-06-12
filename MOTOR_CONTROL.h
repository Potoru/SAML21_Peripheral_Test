#ifndef _MOTOR_CONTROL_H_
#define _MOTOR_CONTROL_H_

#define buffer_min_value 800
#define buffer_init_value 790
#define Motor_Speed_Max 1800



int16_t set_control_power0;
int16_t set_control_power1;
int16_t set_control_power2;
int16_t set_control_power3;

float buffer0;
float buffer1;
float buffer2;
float buffer3;

void Motor_speed_set(void);
void Motor_Init(void);
void motor_zero_set(void);
void Motor_Func(void);

#endif