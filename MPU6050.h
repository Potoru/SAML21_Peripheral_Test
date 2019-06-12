#ifndef _MPU6050_H_
#define _MPU6050_H_
#define  ADDRESS 0x68
#define STRING_BUFFER_SIZE 16
const uint8_t maxRetries;

#define PID_P 8.000
#define PID_I 4.500
#define PID_D 1.500
#define PID_dt 0.044


typedef struct {
	
	float Current_Value;
	float Err;
	float Prev_Err;
	float I_Err;
	float D_Err;
	float P_Value;
	float I_Value;
	float D_Value;
	float Cal_Value;
	
}Gyro_PID_t;

Gyro_PID_t Gyro_PID_AcX, Gyro_PID_AcY, Gyro_PID_AcZ;

typedef struct {
	int16_t Median_Filter_Buffuer_ac[STRING_BUFFER_SIZE];
	int16_t Median_Filter_Cal_Value_ac;
	uint8_t Median_Buffer_Counter;
} Median_MPU6050_t;

Median_MPU6050_t Median_AcX, Median_AcY, Median_AcZ;

uint8_t Ring_buffer_status;
float PID_Roll, PID_Pitch, PID_Yaw;
float Roll;
float Pitch;

void MPU6050_init(void);
void MPU6050_Read_data(void);
void MPU6050_Address_Check(void);
void MPU6050_Read_data_doing(void);
void MPU6050_Calibaration(void);
void MPU6050_Calibaration_Clear(void);


static inline float MPU6050_Median_Filter(Median_MPU6050_t *MMT, int16_t Ac_data)
{
	int32_t Median_Cal_Buffer = 0;
	
	MMT->Median_Filter_Buffuer_ac[MMT->Median_Buffer_Counter] = Ac_data;
	MMT->Median_Buffer_Counter++;
	if(MMT->Median_Buffer_Counter >= STRING_BUFFER_SIZE)
	{
		MMT->Median_Buffer_Counter = 0;
	}
	
	for(uint8_t i = 0; i < STRING_BUFFER_SIZE; i++)
	{
		Median_Cal_Buffer += MMT->Median_Filter_Buffuer_ac[i];
	}
	MMT->Median_Filter_Cal_Value_ac = Median_Cal_Buffer/STRING_BUFFER_SIZE;
	
	return MMT->Median_Filter_Cal_Value_ac;
}


static inline float MPU6050_PID_Control(Gyro_PID_t *GPT, float Angle)
{
	GPT->Err = Angle;					// 목표값과 현재값의 오차 구하기~
	GPT->P_Value = GPT->Err * PID_P;		// 위에서 구한 차이값과 P상수 곱하기
	
	GPT->I_Err = GPT->Err * PID_dt;					// 적분오차값 구하기
	GPT->I_Value = GPT->I_Err * PID_I;				// 적분오차값과 I상수 곱하기
	
	GPT->D_Err = (GPT->Err - GPT->Prev_Err)/PID_dt;	// 미분오차값 구하기
	GPT->D_Value = GPT->D_Err * PID_D;				// 미분오차값과 D상수 곱하기

	GPT->Prev_Err = GPT->Err;						// 현재 값은 이전 값으로 밀어넣기
	
	GPT->Cal_Value = GPT->P_Value +	GPT->I_Value + GPT->D_Value; // 다 더하면 제어값이 나온다

	
	return GPT->Cal_Value;
}

void Gyro_Func(void);

#endif