#ifndef _TC_H_
#define _TC_H_

#include "ALL_HEADER.h"

struct tc_module TC0_Module;
struct tc_module TC1_Module;

struct tc_config TC0_Config; 
struct tc_config TC1_Config;





uint32_t global_timer_count;
uint8_t TC0_delay_sqn ;
uint32_t global_timer_count_tmp ;
uint32_t TC1_Count_Value;

typedef struct{
	uint16_t global_timer_count_tmp;
	uint16_t timer_task_sqn;
	bool timer_task_falg : 1;
	}Timer_Task_t;
	
Timer_Task_t Timer_Task_Gyro_Func_Call;
Timer_Task_t Timer_Task_ADC_Func_Call;

void Timer_Task_Call_Fucntion(Timer_Task_t *const Timer_Task_Type, void (*call_func)(void), uint16_t Count_Value);

void TC0_ISR(struct tc_module *const module_inst);
void TC0_Init(void);
void TC0_Callback_Init(void);
void TC1_ISR(struct tc_module *const module_inst);
void TC1_Callback_Init(void);
void TC1_Init(void);
int TC0_delay_flag(uint16_t count);
void Timer_Task(void);
void Cycle_Check_Timer(void);

#ifdef FREQUENCY_READ

struct tc_module TC2_Module;
struct tc_events TC2_Events;
struct tc_config TC2_Config;
void TC2_Init(void);
uint32_t get_frequency(void);

#endif


#endif