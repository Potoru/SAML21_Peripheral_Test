#include "ALL_HEADER.h"

void TC0_ISR(struct tc_module *const module_inst)
{
	global_timer_count++;
}

void TC0_Init(void)
{

	TC0_Module.hw = TC0;
	
	tc_get_config_defaults(&TC0_Config);
	
	TC0_Config.clock_prescaler = TC_CLOCK_PRESCALER_DIV16;
	TC0_Config.counter_16_bit.compare_capture_channel[0] = 2;
	
	
	while(tc_init(&TC0_Module, TC0, &TC0_Config) != STATUS_OK)
	{
		printf("TC0 Init fail\n\r");
	}
	
	tc_enable(&TC0_Module);

}

void TC0_Callback_Init(void)
{
	while(tc_register_callback(&TC0_Module, TC0_ISR, TC_CALLBACK_CC_CHANNEL0) != STATUS_OK)
	{
		printf("TC0 register fail\n\r");
	}
	
	tc_enable_callback(&TC0_Module, TC_CALLBACK_CC_CHANNEL0);
}

uint8_t TC0_delay_sqn = 0;
uint32_t global_timer_count_delay_tmp = 0;

int TC0_delay_flag(uint16_t count)
{
	uint8_t global_timer_flag0 = 0;
	
	switch (TC0_delay_sqn){
		case 0 : 
			global_timer_count_delay_tmp = global_timer_count;
			TC0_delay_sqn = 1;
			break;
		case 1 :
			if((global_timer_count - global_timer_count_delay_tmp) >= count)
			{
				global_timer_flag0 = 1;
				global_timer_count_delay_tmp = 0;
				TC0_delay_sqn = 0;
			}
			break;
	}
	if(global_timer_flag0 == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

/* hint for use
	1. setting new struct 'Timer_Task_t'
	2. void type function setting
	3. timer value set (uint16_t)
*/

void Timer_Task_Call_Fucntion(Timer_Task_t *const Timer_Task_Type, void (*call_func)(void), uint16_t Count_Value)		//void type function call
{
	switch (Timer_Task_Type->timer_task_sqn){
		case 0 :
		Timer_Task_Type->global_timer_count_tmp = global_timer_count;
		Timer_Task_Type->timer_task_sqn = 1;
		break;
		
		case 1 :
		if(global_timer_count < Timer_Task_Type->global_timer_count_tmp)
		{
			Timer_Task_Type->timer_task_sqn = 0;
		}
		
		if((global_timer_count - Timer_Task_Type->global_timer_count_tmp) >= Count_Value)
		{
			(*call_func)();
			Timer_Task_Type->timer_task_falg = 1;
			Timer_Task_Type->global_timer_count_tmp = 0;
			Timer_Task_Type->timer_task_sqn = 0;
		}
		break;
	}
}


void TC1_ISR(struct tc_module *const module_inst)
{
	TC1_Count_Value++;
}

void TC1_Callback_Init(void)
{
	while(tc_register_callback(&TC1_Module, TC1_ISR, TC_CALLBACK_CC_CHANNEL0) != STATUS_OK)
	{
		printf("TC1 register fail\n\r");
	}
	
	tc_enable_callback(&TC1_Module, TC_CALLBACK_CC_CHANNEL0);
}

void TC1_Init(void)
{

	TC1_Module.hw = TC1;
	
	tc_get_config_defaults(&TC1_Config);
	TC1_Config.clock_source = GCLK_GENERATOR_0;
	TC1_Config.clock_prescaler = TC_CLOCK_PRESCALER_DIV1024;
	TC1_Config.wave_generation = TC_WAVE_GENERATION_MATCH_FREQ;
	TC1_Config.counter_size = TC_COUNTER_SIZE_16BIT;
	TC1_Config.counter_16_bit.value = 0;
	TC1_Config.counter_16_bit.compare_capture_channel[0] = 47;
	
	
	while(tc_init(&TC1_Module, TC1, &TC1_Config) != STATUS_OK)
	{
		printf("TC1 Init fail\n\r");
	}

	tc_enable(&TC1_Module);
	
	TC1_Callback_Init();

}

void Timer_Task(void)
{
	
}

void Cycle_Check_Timer(void)
{
	if(Cycle_Check_Flag == 1)
	{
		printf("%dms\n\r", TC1_Count_Value);
		TC1_Count_Value = 0;
	}
}


//////////////////////////////////////////////////////////////////////////
#ifdef FREQUENCY_READ
void TC2_ISR(struct tc_module *const module_inst)
{
	module_inst->hw->COUNT16.CC[0].reg = 0;
}

void TC2_Callback_Init(void)
{
	while(tc_register_callback(&TC2_Module, TC2_ISR, TC_CALLBACK_OVERFLOW) != STATUS_OK)
	{
		printf("TC2 register fail\n\r");
	}
	
	tc_enable_callback(&TC2_Module, TC_CALLBACK_OVERFLOW);
}

void TC2_Init(void)
{
	TC2_Module.hw = TC2;
	
	tc_get_config_defaults(&TC2_Config);
	TC2_Config.clock_source = GCLK_GENERATOR_0;
	TC2_Config.clock_prescaler = TC_CLOCK_PRESCALER_DIV16;
	TC2_Config.enable_capture_on_channel[TC_COMPARE_CAPTURE_CHANNEL_0] = true;
	TC2_Config.enable_capture_on_channel[TC_COMPARE_CAPTURE_CHANNEL_1] = true;
	TC2_Config.enable_capture_on_IO[TC_COMPARE_CAPTURE_CHANNEL_0] = true;
	TC2_Config.enable_capture_on_IO[TC_COMPARE_CAPTURE_CHANNEL_1] = true;
	
	TC2_Events.generate_event_on_compare_channel[0] = true;
	TC2_Events.generate_event_on_compare_channel[1] = true;
	TC2_Events.on_event_perform_action = true;
	TC2_Events.invert_event_input = true;
	TC2_Events.event_action = TC_EVENT_ACTION_PWP;
	
	while(tc_init(&TC2_Module, TC2, &TC2_Config) != STATUS_OK)
	{
		printf("TC2 Init fail\n\r");
	}
	
	tc_enable_events(&TC2_Module, &TC2_Events);
	tc_enable(&TC2_Module);
	TC2_Callback_Init();
}

uint32_t get_frequency(void)
{
	return tc_get_capture_value(&TC2_Module, TC_COMPARE_CAPTURE_CHANNEL_0);
}

			uint32_t test_freq = 0;
			test_freq = get_frequency();
#endif