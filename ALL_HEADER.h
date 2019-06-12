#ifndef _ALL_HEADER_H_
#define _ALL_HEADER_H_

#define MAIN_DEBUG_MODE_FOR_DISPLAY
#define MOTOR_SPEED_DISPLAY 1
#define UART_RN4870

//#define FREQUENCY_READ
typedef enum{
	_STATE_INIT,
	_STATE_RUN,
	_STATE_STANBY,
	_STATE_SLEEP,
}_state_t;
_state_t MAIN_STATE;


#include <asf.h>
#include <stdint.h>
#include <fastmath.h>
#include <string.h>
#include <stdlib.h>
#include "ADC0.h"
#include "UART.h"
#include "PWM.h"
#include "I2C.h"
#include "PORT_CONTROL.h"
#include "MPU6050.h"
#include "TC.h"
#include "MOTOR_CONTROL.h"
#include "WDT.h"
#include "NVM0.h"

#ifdef	UART_RN4870
#include "RN4870.h"
#endif

#ifdef FREQUENCY_READ
	#include "EXTINT_.h"
	#include "EVENTS_SYSTEM.h"
#endif
//#include "USB0.h"

#endif