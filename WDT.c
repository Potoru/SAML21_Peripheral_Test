#include "ALL_HEADER.h"

void WDT_Init()
{

	wdt_get_config_defaults(&WDT_config);
	WDT_config.timeout_period = WDT_PERIOD_128CLK;
	while(wdt_set_config(&WDT_config) != STATUS_OK);
}