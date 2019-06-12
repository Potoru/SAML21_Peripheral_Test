#include "ALL_HEADER.h"

#define ADDRESS 0x68
#define TEST_VALUE 0.3


const uint8_t maxRetries = 2;
uint8_t Ring_buffer_status = 0;
	
enum status_code powerOnStatus;

void MPU6050_init(void)
{
	uint8_t retryCount = 0;

	static uint8_t buffer[2] = { 0x6b, 0x0 }; // power on packet
	struct i2c_master_packet packet = {
		.address = ADDRESS,
		.data = buffer,
		.data_length = 2,
	};

	while ((powerOnStatus = i2c_master_write_packet_wait(&I2C_Module0, &packet)) != STATUS_OK)
	{
		if (++retryCount >= maxRetries) break;
	}
	if(powerOnStatus == STATUS_OK)
	{
		printf("Zyro power on\n\r");
	}
	else
	{
		printf("Zyro power on fail\n\r");
	}
}

	static uint8_t buffer[14] = { 0x75, 0x00, }; // who am I
	uint8_t whoAmI = 0;
	
void MPU6050_Address_Check(void)
{

	while(!(TC0_delay_flag(5)))
	{
		asm("nop");
	}
	

	struct i2c_master_packet Packet = {
		.address = ADDRESS,
		.data = buffer,
		.data_length = 1,
	};
	// here use the no_stop variant

	while (i2c_master_write_packet_wait_no_stop(&I2C_Module0, &Packet) != STATUS_OK)
	{
		printf("nonono\n\r");
	}

	i2c_master_read_packet_wait(&I2C_Module0, &Packet);
	whoAmI = buffer[0];
	printf("Zyro Address is 0x%x \n\r" ,whoAmI);

}

// give the sensor 50 ms. to gather some data
uint8_t MPU6050_Read_sqn = 0;
void MPU6050_Read_data(void)
{
	switch (MPU6050_Read_sqn) {
		case 0 : 
			if(TC0_delay_flag(5) == true)
			{
				MPU6050_Read_sqn = 1;
			}
			break;
		case 1 :
			MPU6050_Read_data_doing();
			MPU6050_Read_sqn = 0;
			break;

	}
}


int Cal_gyX = 1;
int Cal_gyY = 1;
int Cal_gyZ = 1;
int Cal_acX = 1;
int Cal_acY = 1;
int Cal_acZ = 1;

int16_t Medi_acX;
int16_t Medi_acY;
int16_t Medi_acZ;

float Roll = 0.0;
float Pitch = 0.0;
float Yaw = 0.0;

float acX_filter, acY_filter, acZ_filter;


void MPU6050_Read_data_doing(void)
{
	uint8_t retryCount = 0;
	// send 1 byte with the offset we want to read
	static uint8_t writeBuffer[1] = { 0x3B }; // ACCEL_XOUT_H location
	struct i2c_master_packet packet = {
		.address = ADDRESS,
		.data = writeBuffer,
		.data_length = 1,
	};
	while (i2c_master_write_packet_wait_no_stop(&I2C_Module0, &packet) != STATUS_OK)
	{
		if (++retryCount >= maxRetries) break;
	}
	// now do the actual reading

	struct i2c_master_packet readPacket = {
		.address = ADDRESS,
		.data = buffer,
		.data_length = 14,
	};
			
	while (i2c_master_read_packet_wait(&I2C_Module0, &readPacket) != STATUS_OK)
	{
		if (++retryCount >= maxRetries) break;
	}

	int16_t acX = buffer[0] << 8 | buffer[1]; // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
	int16_t acY = buffer[2] << 8 | buffer[3]; // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
	int16_t acZ = buffer[4] << 8 | buffer[5]; // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
	//		int16_t tmp = buffer[6] << 8 | buffer[7]; // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
//	int16_t gyX = buffer[8] << 8 | buffer[9]; // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
//	int16_t gyY = buffer[10] << 8 | buffer[11]; // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
//	int16_t gyZ = buffer[12] << 8 | buffer[13]; // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
	
// 	acX_filter = (TEST_VALUE*acX_filter)+((1-TEST_VALUE)*acX);
// 	acY_filter = (TEST_VALUE*acY_filter)+((1-TEST_VALUE)*acY);
// 	acZ_filter = (TEST_VALUE*acZ_filter)+((1-TEST_VALUE)*acZ);	

	
	acX_filter = (TEST_VALUE*acX_filter)+((1-TEST_VALUE)*MPU6050_Median_Filter(&Median_AcX, acX));
	acY_filter = (TEST_VALUE*acY_filter)+((1-TEST_VALUE)*MPU6050_Median_Filter(&Median_AcY, acY));
	acZ_filter = (TEST_VALUE*acZ_filter)+((1-TEST_VALUE)*MPU6050_Median_Filter(&Median_AcZ, acZ));


	Roll = 180 * atan(acY_filter/sqrt(acX_filter*acX_filter + acZ_filter*acZ_filter))/M_PI;
	Pitch = 180 * atan(acX_filter/sqrt(acY_filter*acY_filter + acZ_filter*acZ_filter))/M_PI;
	Yaw = 180 * atan(acY_filter/acX_filter)/M_PI;
	
	PID_Roll = MPU6050_PID_Control(&Gyro_PID_AcX, Roll);
	PID_Pitch = MPU6050_PID_Control(&Gyro_PID_AcY, Pitch);
	PID_Yaw = MPU6050_PID_Control(&Gyro_PID_AcZ, Yaw);
	
#ifdef MAIN_DEBUG_MODE_FOR_DISPLAY

	printf("PID_X = %f - ", PID_Roll);
	printf("PID_Y = %f - ", PID_Pitch);
	printf("PID_Z = %f - ", PID_Yaw);
	// 	printf("Roll_P = %f ", PID_Roll);
	// 	printf("Pitch_P = %f ", PID_Pitch);
	// 	printf("Yaw_P = %f ", PID_Yaw);

	printf("Roll = %f ", Roll);
	printf("Pitch = %f\n\r", Pitch);
	//	printf("Yaw = %f\n\r", Yaw);
	// send the data off
#endif

}

void Gyro_Func(void)
{
	if(Zyro_Flag == 1)
	{
		MPU6050_Read_data();
	}
}