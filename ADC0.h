#ifndef _ADC0_H_
#define _ADC0_H_

#define ADC_TEMP_SENSOR_ZERO_POSITION 510

#define ADC_READ_INTERVAL 10

uint16_t ADC_Value;
int ADC_Voltage_Value;
struct adc_module ADC_Module0;
struct adc_config ADC_Config0;

void ADC_Init(void);
int ADC_Read_Voltage(void);
void ADC_Read_Voltage_Void(void);
int ADC_Temp_Sensor(void);
void ADC_Func(void);
void _ADC_Func_Call(void);

#endif