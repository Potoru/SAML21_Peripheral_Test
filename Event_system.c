#include "ALL_HEADER.h"

void Event_Init(void)
{
	#ifdef FREQUENCY_READ
	events_get_config_defaults(&Events_Config0);
	Events_Config0.generator = EVSYS_ID_GEN_EIC_EXTINT_0;
	Events_Config0.edge_detect = EVENTS_EDGE_DETECT_BOTH;
	Events_Config0.path = EVENTS_PATH_ASYNCHRONOUS;
	
	events_allocate(&Events_Resource_Extint0, &Events_Config0);
	
	events_attach_user(&Events_Resource_Extint0, EVSYS_ID_USER_TC2_EVU);
	#endif
}