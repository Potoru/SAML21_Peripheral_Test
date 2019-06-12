#include "ALL_HEADER.h"

void Motor_Init()
{

	REG_TCC0_CC0 = buffer_init_value;

	REG_TCC0_CC1 = buffer_init_value;

	REG_TCC0_CC2 = buffer_init_value;

	REG_TCC0_CC3 = buffer_init_value;
}

void Motor_speed_set()
{
	
	
	buffer0 = buffer_init_value + set_control_power0 + (PID_Roll * -2) + (PID_Pitch * -2);		//left front	PA8
	buffer1 = buffer_init_value + set_control_power1 + (PID_Roll * 2) + (PID_Pitch * -2);		//right front	PA9
	buffer2 = buffer_init_value + set_control_power2 + (PID_Roll * -2) + (PID_Pitch * 2);		//left back		PA10
	buffer3 = buffer_init_value + set_control_power3 + (PID_Roll * 2) + (PID_Pitch * 2);		//right back	PA11
	

	if((REG_TCC0_CC0 = buffer0) >= Motor_Speed_Max)
	{
#ifdef MOTOR_SPEED_DISPLAY
//		REG_TCC0_CC0 = REG_TCC0_CC0_old_buffer;
		printf("The value was not applied\n\r");
		printf("buffer0 value was applied the old buffer\n\r");
#endif
	}
	else if(buffer0 < buffer_min_value)
	{
		REG_TCC0_CC0 = buffer_min_value;
	}
	//	buffer1 = ;	
	if((REG_TCC0_CC1 = buffer1) >= Motor_Speed_Max)
	{
#ifdef MOTOR_SPEED_DISPLAY
//		REG_TCC0_CC1 = REG_TCC0_CC1_old_buffer;
		printf("The value was not applied\n\r");
		printf("buffer1 value was applied the old buffer\n\r");
#endif
	}
	else if(buffer1 < buffer_min_value)
	{
		REG_TCC0_CC1 = buffer_min_value;
	}
	//	buffer2 = ;
	if((REG_TCC0_CC2 = buffer2) >= Motor_Speed_Max)
	{
#ifdef MOTOR_SPEED_DISPLAY
//		REG_TCC0_CC2 = REG_TCC0_CC2_old_buffer;
		printf("The value was not applied\n\r");
		printf("buffer2 value was applied the old buffer\n\r");
#endif
	}
	else if(buffer2 < buffer_min_value)
	{
		REG_TCC0_CC2 = buffer_min_value;
	}
	//	buffer3 = ;
	if((REG_TCC0_CC3 = buffer3) >= Motor_Speed_Max)
	{
#ifdef MOTOR_SPEED_DISPLAY
//		REG_TCC0_CC3 = REG_TCC0_CC3_old_buffer;
		printf("The value was not applied\n\r");
		printf("buffer3 value was applied the old buffer\n\r");
#endif
	}
	else if(buffer3 < buffer_min_value)
	{
		REG_TCC0_CC3 = buffer_min_value;
	}
	
#ifdef MOTOR_SPEED_DISPLAY

	printf("Motor1 %d Motor2 %d Motor3 %d Motor4 %d\n\r", REG_TCC0_CC0, REG_TCC0_CC1, REG_TCC0_CC2, REG_TCC0_CC3);

#endif

}

void motor_zero_set(void)
{
	REG_TCC0_CC0 = 0;
	REG_TCC0_CC1 = 0;
	REG_TCC0_CC2 = 0;
	REG_TCC0_CC3 = 0;
}

void Motor_Func(void)
{
	if(Motor_Flag == 1)
	{
		Motor_speed_set();
	}
	else if(Motor_Flag == 0)
	{
		motor_zero_set();
	}
}