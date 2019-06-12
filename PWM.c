#include "ALL_HEADER.h"

uint16_t Duty_set = 0;

void PWM_module0_motor_Init(void)
{
	
	PWM0_Module.hw = TCC0;
	tcc_get_config_defaults(&PWM0_config, TCC0);
	PWM0_config.counter.clock_source = GCLK_GENERATOR_0;
	PWM0_config.counter.clock_prescaler = TCC_CLOCK_PRESCALER_DIV64;
	PWM0_config.counter.reload_action = TCC_RELOAD_ACTION_GCLK;
	PWM0_config.counter.period = 2000;
	PWM0_config.compare.wave_generation = TCC_WAVE_GENERATION_SINGLE_SLOPE_PWM;
	//channel 1
	PWM0_config.compare.match[0] = 0;
	PWM0_config.pins.enable_wave_out_pin[0] = true;
	PWM0_config.pins.wave_out_pin[0] = PIN_PA08E_TCC0_WO0;
	PWM0_config.pins.wave_out_pin_mux[0] = MUX_PA08E_TCC0_WO0;

	PWM0_config.compare.match[1] = 0;
	PWM0_config.pins.enable_wave_out_pin[1] = true;
	PWM0_config.pins.wave_out_pin[1] = PIN_PA09E_TCC0_WO1;
	PWM0_config.pins.wave_out_pin_mux[1] = MUX_PA09E_TCC0_WO1;
	
	PWM0_config.compare.match[2] = 0;
	PWM0_config.pins.enable_wave_out_pin[2] = true;
	PWM0_config.pins.wave_out_pin[2] = PIN_PA10F_TCC0_WO2;
	PWM0_config.pins.wave_out_pin_mux[2] = MUX_PA10F_TCC0_WO2;
	
	PWM0_config.compare.match[3] = 0;
	PWM0_config.pins.enable_wave_out_pin[3] = true;
	PWM0_config.pins.wave_out_pin[3] = PIN_PA11F_TCC0_WO3;
	PWM0_config.pins.wave_out_pin_mux[3] = MUX_PA11F_TCC0_WO3;

	
	while(tcc_init(&PWM0_Module, TCC0, &PWM0_config) != STATUS_OK);

	
	tcc_enable(&PWM0_Module);
}

// void PWM_module1_RGB_LED_Init(void)
// {
// 	PWM1_Module.hw = TCC1;
// 	tcc_get_config_defaults(&PWM1_config, TCC1);
// 
// 	PWM1_config.counter.clock_source = GCLK_GENERATOR_0;
// 	PWM1_config.counter.clock_prescaler = TCC_CLOCK_PRESCALER_DIV16;
// 	PWM1_config.counter.reload_action = TCC_RELOAD_ACTION_GCLK;
// 	PWM1_config.counter.period = 1000;
// 	PWM1_config.compare.wave_generation = TCC_WAVE_GENERATION_SINGLE_SLOPE_PWM;
// 	//Red
// 	PWM1_config.compare.match[0] = 0;
// 	PWM1_config.pins.enable_wave_out_pin[0] = true;
// //	PWM1_config.pins.wave_out_pin[0] = 
// //	PWM1_config.pins.wave_out_pin_mux[0] = ;
// 	//Green
// 	PWM1_config.compare.match[1] = 0;
// 	PWM1_config.pins.enable_wave_out_pin[1] = true;
// //	PWM1_config.pins.wave_out_pin[1] = ;
// //	PWM1_config.pins.wave_out_pin_mux[1] = ;
// 	//Blue
// 	PWM1_config.compare.match[2] = 0;
// 	PWM1_config.pins.enable_wave_out_pin[2] = true;
// //	PWM1_config.pins.wave_out_pin[2] = ;
// //	PWM1_config.pins.wave_out_pin_mux[2] = ;
// 	
// 	while(tcc_init(&PWM1_Module, TCC1, &PWM1_config) != STATUS_OK);
// 
// 	
// 	tcc_enable(&PWM1_Module);
// }
// 
