#include "ALL_HEADER.h"

void PORT_Init(void)
{
	port_get_config_defaults(&port_conf_set);
#if 1
	port_conf_set.direction = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(PIN_PB10, &port_conf_set);

	port_conf_set.direction = PORT_PIN_DIR_INPUT;
	port_conf_set.input_pull = PORT_PIN_PULL_UP;
	port_pin_set_config(PIN_PA02, &port_conf_set);
#endif

#if 0
	port_conf_set.direction = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(PIN_PA04, &port_conf_set);
	port_pin_set_config(PIN_PA05, &port_conf_set);
	port_pin_set_config(PIN_PA06, &port_conf_set);
	port_pin_set_config(PIN_PA07, &port_conf_set);
	
	
#endif
}