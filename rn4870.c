
#include "ALL_HEADER.h"
#ifdef UART_RN4870

void BLE_Command_Task(void)
{
	RN4870_Init();
}

void RN4870_Init(void)
{
	if(BLE_Init == true)
	{
		BLE_Init = false;
		uint16_t ttp = 0x0d;
	//	RN4870_UART_Write("\n");
	usart_write_job(&USART1_Module, &ttp);
		
		printf("BLE Init\n\r");
	}
}

void RN4870_UART_Write(uint8_t *_sting)
{
	while(usart_write_buffer_job(&USART1_Module, _sting, sizeof(_sting)) != STATUS_OK);
}

#endif