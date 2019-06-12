#ifndef _SH_UART_H_
#define _SH_UART_H_

#define USART_CALLBACK_MODE true
#define uart_debug_stream_buffer_size 200
#define COMMAND_COUNT 15
#define COMMAND_CALIBRATION_VALUE 1

char uart_data_command_buffer[uart_debug_stream_buffer_size];


struct usart_module USART0_Module;
struct usart_config USART0_Config;

typedef struct {
	unsigned char front_position;									//링 버퍼의 첫단 위치
	unsigned char end_position;									//링 버퍼의 끝단 위치 *별개로 현위치는 돌아가는 함수에서 선언한다.
	unsigned char ring_data[uart_debug_stream_buffer_size];	//링 버퍼에 들어갈 데이터
}Ring_buffer_t;

void command_detect(void);
int Ring_buffer_read(Ring_buffer_t *ring_buffer);
int Ring_buffer_write(Ring_buffer_t *Ring_buffer, char data);
int two_point_cal(int data1, int data2);
int UART_Debug_Mode(uint8_t data);
void Uart_Init(void);
void USART0_Callback_Init(void);
void USART0_RX_ISR(struct usart_module *const module);
void command_request(uint8_t sw);
char *command_function(uint8_t sw);

uint16_t uart0_callback_buffer;


uint8_t Motor_Flag;
uint8_t Zyro_Flag;
uint8_t ADC_Flag;
uint8_t Cycle_Check_Flag;
bool BLE_Init;
//---------------------------------------------


#ifdef UART_RN4870

struct usart_module USART1_Module;
struct usart_config USART1_Config;
void Uart_Init_RN4870(void);
uint16_t *uart1_callback_buffer;
void USART1_Callback_Init(void);
void USART1_RX_ISR(struct usart_module *const module);
Ring_buffer_t RN4870_Ring_Buffer;

#endif



#endif