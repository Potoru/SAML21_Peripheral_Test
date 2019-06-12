#include "ALL_HEADER.h"

void App_Task(void);
void Main_Init(void);

int main (void)
{
	Main_Init();
	
	while(1)
	{
		App_Task();
		
	}

}

void Main_Init(void)
{
	system_interrupt_disable_global();
	/*******************************************/
	system_init();

	TC0_Init();
	TC0_Callback_Init();
	TC1_Init();
#ifdef FREQUENCY_READ
	TC2_Init(); // test
	Extint_Init();// test
	Event_Init();
#endif
#ifdef UART_RN4870
	Uart_Init_RN4870();
#endif
	PORT_Init();
	I2C_Init();
	Uart_Init();
	Motor_Init();
	ADC_Init();
	NVM_Init();
	sleepmgr_init();
	PWM_module0_motor_Init();
	
	/*	dsu_crc32_init();*/
	/*******************************************/
	system_interrupt_enable_global();
	
	/*******************************************/
	MPU6050_init();
	MPU6050_Address_Check();

	//	USB0_Init();
	/*******************************************/
	printf("System Init Complete\r\n");
	/*******************************************/
}
uint16_t pt = 123;
void App_Task(void)
{
	switch (MAIN_STATE)
	{
		case _STATE_INIT:
			WDT_Init(); // �ظ��ϸ� ��ġ���� �������� �̴ϼȶ���¡ �ϴ°ŷ�~^^	

			MAIN_STATE = _STATE_RUN;
		break;
		
		case _STATE_RUN:
#ifdef UART_RN4870
			BLE_Command_Task();
#endif
			ADC_Func();
			Gyro_Func();
			Motor_Func();

			Cycle_Check_Timer();

		break;
		
		case _STATE_STANBY:
			ADC_Func();
		break;

		case _STATE_SLEEP:
			asm("nop");
		break;
		
		default:
			asm("nop");
			MAIN_STATE = _STATE_INIT;
		break;
	}
	wdt_reset_count();	// �ҽ� ������ ������ �� ��ġ�� ī��Ʈ�� ����������� Enable�س��� ��� ���µȴ�
}

