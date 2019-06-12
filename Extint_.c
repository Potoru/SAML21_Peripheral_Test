#include "ALL_HEADER.h"


void Extint_Init(void)
{
	#ifdef FREQUENCY_READ
	extint_chan_get_config_defaults(&Extint_Config);
	Extint_Config.gpio_pin = PIN_PB16A_EIC_EXTINT0;
	Extint_Config.gpio_pin_mux = MUX_PB16A_EIC_EXTINT0;
	Extint_Config.gpio_pin_pull = EXTINT_PULL_UP;
	Extint_Config.detection_criteria = EXTINT_DETECT_HIGH;
	
	extint_chan_set_config(0, &Extint_Config);
	
	Extint_Events.generate_event_on_detect[0] = true;
	extint_enable_events(&Extint_Events);
	#endif
}
