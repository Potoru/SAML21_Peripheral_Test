#include "ALL_HEADER.h"

#ifdef UART_RN4870

void USART1_RX_ISR(struct usart_module *const module)
{
	uint16_t *RX_ISR_buffer;
//	while(usart_read_buffer_wait(&USART1_Module, uart1_callback_buffer, 3) != STATUS_OK);
	while(usart_read_wait(&USART1_Module, &uart1_callback_buffer) != STATUS_OK);
	
	printf("value : %c\n\r", uart1_callback_buffer);
	
	SercomUsart *const usart_hw = &(USART1_Module.hw->USART);
	usart_hw-> INTENSET.reg = SERCOM_USART_INTENSET_RXS;
}

void USART1_Callback_Init(void)
{
	usart_register_callback(&USART1_Module, USART1_RX_ISR, USART_CALLBACK_START_RECEIVED);
	usart_enable_callback(&USART1_Module, USART_CALLBACK_START_RECEIVED);

	/* Get a pointer to the hardware module instance */
	SercomUsart * const usart_hw = & (USART1_Module.hw-> USART);
	usart_hw-> INTENSET.reg = SERCOM_USART_INTENSET_RXS;	// 수동으로 레지스터 값을 변경해준거당
}

void Uart_Init_RN4870(void)
{
	USART1_Module.hw = SERCOM2;
	USART1_Module.receiver_enabled = true;
	USART1_Module.transmitter_enabled = true;
	USART1_Module.callback_enable_mask = true;
	
	usart_get_config_defaults(&USART1_Config);
	USART1_Config.baudrate = 115200;
	USART1_Config.data_order = USART_DATAORDER_LSB;
	USART1_Config.transfer_mode = USART_TRANSFER_ASYNCHRONOUSLY;
	USART1_Config.parity = USART_PARITY_NONE;
	USART1_Config.stopbits = USART_STOPBITS_1;
	USART1_Config.character_size = USART_CHARACTER_SIZE_8BIT;
	USART1_Config.mux_setting = USART_RX_1_TX_0_XCK_1;
	USART1_Config.pinmux_pad0 = PINMUX_PA12C_SERCOM2_PAD0;		//TX Orange
	USART1_Config.pinmux_pad1 = PINMUX_PA13C_SERCOM2_PAD1;		//RX Yellow
	USART1_Config.pinmux_pad2 = PINMUX_UNUSED;
	USART1_Config.pinmux_pad3 = PINMUX_UNUSED;
	USART1_Config.start_frame_detection_enable = true;
	
	while(!(usart_serial_init(&USART1_Module, SERCOM2, &USART1_Config)));
	usart_enable(&USART1_Module);
	
	USART1_Callback_Init();
}


#endif



	
Ring_buffer_t Ring_buffer_uart_stream;

char *command_function(uint8_t sw)
{
	const char *Command_arry[COMMAND_COUNT] = { 
		"MSTR",		// 0
		"MSTP",		// 1
		"ZSTR",		// 2
		"ZSTP",		// 3
		"ADSTR",	// 4
		"ADSTP",	// 5
		"TCHEKSTR", // 6
		"TCHEKSTP", // 7
		"+",		// 8
		"-",		// 9
		"BLEINIT",	// 10
		"BLEreserve", // 11
		"BLEreserve", // 12
		"BLEreserve", // 13
		"BLEreserve"  // 14
	};

	if(sw >= ((sizeof(Command_arry)/sizeof(Command_arry[0]))))
	{
		return NULL;
	}
	
	return Command_arry[sw];
	
/*
	unsigned char str[10];
	
	char *str_addr = &str;
	switch(sw){

		case 0:	str[10] = "MSTR";		break;
		case 1:	str[10] = "MSTP";		break;
		case 2:	str[10] = "ZSTR";		break;
		case 3:	str[10] = "ZSTP";		break;
		case 4:	str[10] = "ADSTR";		break;
		case 5:	str[10] = "ADSTP";		break;
		case 6:	str[10] = "TCHEKSTR";	break;
		case 7:	str[10] = "TCHEKSTP";	break;
		case 8:	str[10] = "+";			break;
		case 9:	str[10] = "-";			break;
		default:					break;
	}
*/

/*
	char *str = malloc(sizeof(char)*10);		// malloc 함수를 이용해서 char * 10크기의 메모리를 str주소부터 예약해놓음
	// 동적 메모리 할당
	switch(sw){
		case 0:	strcpy(str, "MSTR");		break;
		case 1:	strcpy(str, "MSTP");		break;
		case 2:	strcpy(str, "ZSTR");		break;
		case 3:	strcpy(str, "ZSTP");		break;
		case 4:	strcpy(str, "ADSTR");		break;
		case 5:	strcpy(str, "ADSTP");		break;
		case 6:	strcpy(str, "TCHEKSTR");	break;
		case 7:	strcpy(str, "TCHEKSTP");	break;
		case 8:	strcpy(str, "+");			break;
		case 9:	strcpy(str, "-");			break;
		default:	break;
	}
*/
}

void command_request(uint8_t sw)
{
	switch(sw){
		case 0:
			Motor_Flag = 1;
		break;
		
		case 1:
			Motor_Flag = 0;
		break;
		
		case 2:
			Zyro_Flag = 1;
		break;
		
		case 3:
			Zyro_Flag = 0;
		break;
		
		case 4:
			ADC_Flag = 1;
		break;
		
		case 5:
			ADC_Flag = 0;
		break;
		
		case 6:
			Cycle_Check_Flag = 1;
		break;
		
		case 7:
			Cycle_Check_Flag = 0;
		break;
		
		case 8:
			set_control_power0 += 10;
			set_control_power1 += 10;
			set_control_power2 += 10;
			set_control_power3 += 10;
		break;
		
		case 9:
			set_control_power0 -= 10;
			set_control_power1 -= 10;
			set_control_power2 -= 10;
			set_control_power3 -= 10;
		break;
		
		case 10 :
			BLE_Init = true;
			
		case 11 : 
		
		break;

		case 12 :
		
		break;

		case 13 :
		
		break;

		case 14 :
		
		break;		
						
		default:
		break;
	}
}

int two_point_cal(int data1, int data2) // data1은 front, data2는 end
{
	char d = 0;
	if(data1 > data2)
	{
		d = (data1-data2);
		return d;
	}
	else if(data1 == data2)
	{
		d = 0;
		return d;
	}
	else
	{
		d = ((data1+uart_debug_stream_buffer_size)-data2);
		return d;
	}
}

int Ring_buffer_write(Ring_buffer_t *Ring_buffer, char data)
{
	unsigned char next_position = (Ring_buffer->front_position+1) % (uart_debug_stream_buffer_size + 1);
	if(next_position == Ring_buffer->end_position)
	{
		return false; // 현재 위치와 엔드 포지션 위치가 같으면 꽉찬거니까 그냥 나가버린다!
	}

	Ring_buffer->ring_data[Ring_buffer->front_position] = data;		// 현재 위치에
	Ring_buffer->front_position = next_position;
		
	return true;
}

int Ring_buffer_read(Ring_buffer_t *ring_buffer)
{
	uint8_t d;
	uint8_t next_position = (ring_buffer->end_position + 1) % (uart_debug_stream_buffer_size + 1);
	if(ring_buffer->end_position == ring_buffer->front_position)
	{
		return false;
	}
	d = ring_buffer->ring_data[ring_buffer->end_position];
	ring_buffer->end_position = next_position;
	
	return d;
}

void command_detect(void)
{
	
	for(uint8_t i = 0; i < COMMAND_COUNT; i++)
	{

		if(!(strcmp(uart_data_command_buffer, command_function(i))))	// string memory comparation
		{
			command_request(i);
		}
	}
}

int UART_Debug_Mode(uint8_t data)
{

	if(data == 0x08)   // back space 기능이고 현재 위치 데이터를 Null로 바꾸고 프론트 위치를 뒤로 한칸 밀어버림
	{
		Ring_buffer_uart_stream.ring_data[Ring_buffer_uart_stream.front_position] = 0;
		Ring_buffer_uart_stream.front_position -= 1;
		return 0; // 그리고 바로 소스 끝
	}
	
	if(data == 0xd)		// enter기능임
	{
		printf("\n\r");		// printf문으로 줄바꿈 왼쪽 정렬시킴
		uint8_t two_point_cal_value = two_point_cal(Ring_buffer_uart_stream.front_position, Ring_buffer_uart_stream.end_position);
		for(uint8_t i = 0; i < two_point_cal_value; i++)
		{
			uart_data_command_buffer[i] = Ring_buffer_read(&Ring_buffer_uart_stream);		// 커맨드 체크용 버퍼에 데이터를 쪼로록 넣는다
		}

		if(two_point_cal_value > 0)
		{
			command_detect();
		}
		
//		uint32_t test = 0;
// 		while((dsu_crc32_cal(&uart_data_command_buffer, uart_debug_stream_buffer_size, &test) != STATUS_OK));
// 		printf("CRC32 Cal done : 0x%x\n\r", test);
		memset(&uart_data_command_buffer, 0, uart_debug_stream_buffer_size);
		return 0;
	}
	Ring_buffer_write(&Ring_buffer_uart_stream, data);
	return true;
	
}

void USART0_RX_ISR(struct usart_module *const module)
{
	uint16_t RX_ISR_buffer = 0;
	while(usart_read_wait(&USART0_Module, &uart0_callback_buffer) != STATUS_OK);
	RX_ISR_buffer = uart0_callback_buffer;
	while(usart_write_wait(&USART0_Module, RX_ISR_buffer) != STATUS_OK);
	UART_Debug_Mode(RX_ISR_buffer);

	SercomUsart *const usart_hw = &(USART0_Module.hw->USART);
	usart_hw-> INTENSET.reg = SERCOM_USART_INTENSET_RXS;
}

void USART0_Callback_Init(void)
{
	usart_register_callback(&USART0_Module, USART0_RX_ISR, USART_CALLBACK_START_RECEIVED);
	usart_enable_callback(&USART0_Module, USART_CALLBACK_START_RECEIVED);

	/* Get a pointer to the hardware module instance */
 	SercomUsart * const usart_hw = & (USART0_Module.hw-> USART);
 	usart_hw-> INTENSET.reg = SERCOM_USART_INTENSET_RXS;	// 수동으로 레지스터 값을 변경해준거당 receive start interrupt enable 레지스터를 바꿔준거임
}

void Uart_Init(void)
{
	USART0_Module.hw = SERCOM3;
	USART0_Module.receiver_enabled = true;
	USART0_Module.transmitter_enabled = true;
	USART0_Module.callback_enable_mask = true;
	
	usart_get_config_defaults(&USART0_Config);
	USART0_Config.baudrate = 38400;
	USART0_Config.data_order = USART_DATAORDER_LSB;
	USART0_Config.transfer_mode = USART_TRANSFER_ASYNCHRONOUSLY;
	USART0_Config.parity = USART_PARITY_NONE;
	USART0_Config.stopbits = USART_STOPBITS_1;
	USART0_Config.character_size = USART_CHARACTER_SIZE_8BIT;
	USART0_Config.mux_setting = USART_RX_1_TX_0_XCK_1;
	USART0_Config.pinmux_pad0 = PINMUX_PA22C_SERCOM3_PAD0;		//TX
	USART0_Config.pinmux_pad1 = PINMUX_PA23C_SERCOM3_PAD1;		//RX
	USART0_Config.pinmux_pad2 = PINMUX_UNUSED;
	USART0_Config.pinmux_pad3 = PINMUX_UNUSED;
	USART0_Config.start_frame_detection_enable = true;
	
	while(!(usart_serial_init(&USART0_Module, SERCOM3, &USART0_Config)));
	usart_enable(&USART0_Module);
	
	USART0_Callback_Init();
	
	stdio_serial_init(&USART0_Module, SERCOM3, &USART0_Config);
}

