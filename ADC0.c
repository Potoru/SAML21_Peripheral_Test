#include "ALL_HEADER.h"


uint16_t ADC_Value = 0;

void ADC_Init(void)
{
	adc_get_config_defaults(&ADC_Config0);
	ADC_Config0.reference = ADC_REFCTRL_REFSEL_INTVCC2; //VDDANA로 입력되는 전원
	ADC_Config0.positive_input = ADC_POSITIVE_INPUT_PIN13;
	ADC_Config0.negative_input = ADC_NEGATIVE_INPUT_GND;
	ADC_Config0.clock_prescaler = ADC_CLOCK_PRESCALER_DIV4;
	ADC_Config0.sample_length = 1;

	
	while(STATUS_OK != adc_init(&ADC_Module0, ADC ,&ADC_Config0));
	
	while(STATUS_OK != adc_enable(&ADC_Module0));
	
}

int ADC_Read_Voltage(void)
{
	uint16_t ADC_Value_cache = 0;
	adc_read(&ADC_Module0, &ADC_Value_cache);
	
	return ((3300 * ADC_Value_cache)/4092);
}

void ADC_Read_Voltage_Void(void)
{
	uint16_t ADC_Value_cache = 0;
	adc_read(&ADC_Module0, &ADC_Value_cache);
	
	ADC_Voltage_Value = ((3300 * ADC_Value_cache)/4092);
}

int ADC_Temp_Sensor(void)
{
	ADC_Read_Voltage_Void();
	int ADC_Value_cache = ADC_Voltage_Value;
	
	if(ADC_Value_cache <= ADC_TEMP_SENSOR_ZERO_POSITION)
	{
		return (-50 + ((ADC_Value_cache-ADC_TEMP_SENSOR_ZERO_POSITION) / 10));
	}
	else
	{
		return ((ADC_Value_cache-ADC_TEMP_SENSOR_ZERO_POSITION));
	}
	
	
}

void _ADC_Func_Call(void)
{
	if(ADC_Flag == 1)
	{
		adc_start_conversion(&ADC_Module0);
		if(adc_read(&ADC_Module0, &ADC_Value) == STATUS_OK)
		{
			printf("%d\n\r", ADC_Value);
		}
		else if(adc_read(&ADC_Module0, &ADC_Value) == STATUS_BUSY)
		{
			printf("status is busy\n\r");
		}
	}
}

void ADC_Func(void)
{
	Timer_Task_Call_Fucntion(&Timer_Task_ADC_Func_Call, _ADC_Func_Call, ADC_READ_INTERVAL);
}

