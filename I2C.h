#ifndef _I2C_H_
#define _I2C_H_

//uint8_t I2C_Data[10];


struct i2c_master_module I2C_Module0;
struct i2c_master_config I2C_config0;
struct i2c_master_packet I2C_Packet0;

void I2C_Init(void);
void I2C_Master_write_data(char data);

#endif