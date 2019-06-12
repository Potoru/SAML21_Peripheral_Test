#ifndef _RN4870_H_
#define _RN4870_H_

#define RN4870_UART_STRING_SIZE 20

// PA15 GPIO ¤¡¤¡
// false = test_mode
// true = app_mode

void RN4870_Init(void);
void RN4870_UART_Write(uint8_t *_sting);
void BLE_Command_Task(void);

#endif