#include "ALL_HEADER.h"

uint8_t I2C_Data[10] = {
	0x01, 0x02, 0x03, 0x01, 0x02, 0x03, 0x01, 0x02, 0x03, 0xFF
};

void I2C_Init(void)
{

	I2C_Module0.hw = SERCOM4;

	i2c_master_get_config_defaults(&I2C_config0);
	

	I2C_config0.generator_source = GCLK_GENERATOR_0;
	I2C_config0.start_hold_time = I2C_MASTER_START_HOLD_TIME_50NS_100NS;
	I2C_config0.buffer_timeout = 500;							// 재시도 하는 횟수가 아니라 기다리는 시간이야
	I2C_config0.pinmux_pad0 = PINMUX_PB12C_SERCOM4_PAD0;
	I2C_config0.pinmux_pad1 = PINMUX_PB13C_SERCOM4_PAD1;
	I2C_config0.scl_low_timeout = true;
	
	I2C_config0.baud_rate = I2C_MASTER_BAUD_RATE_100KHZ;
	
	while(i2c_master_init(&I2C_Module0, SERCOM4, &I2C_config0) != STATUS_OK);
	
	I2C_Packet0.address = 0x68;
	I2C_Packet0.data = I2C_Data;
	I2C_Packet0.data_length = 1;
	I2C_Packet0.high_speed = false;
	I2C_Packet0.hs_master_code = 0;
	I2C_Packet0.ten_bit_address = false;
	
	
	i2c_master_enable(&I2C_Module0);

}


void I2C_Master_write_data(char data)
{
	i2c_master_write_byte(&I2C_Module0, data);
	
}