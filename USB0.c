#include "ALL_HEADER.h"

void USB_Suspend_ISR(struct usb_module *module_inst, void* pointer)
{
	printf("USB is Suspended\n\r");
}

void USB_SOF_ISR(struct usb_module *module_inst, void* pointer)
{
	printf("USB is Start\n\r");
	
}

void USB_RESET_ISR(struct usb_module *module_inst, void* pointer)
{
	printf("USB reset\n\r");
}

void USB0_Callback_Init(void)
{
	usb_device_register_callback(&usb_device, USB_DEVICE_CALLBACK_SOF, USB_SOF_ISR);
	usb_device_enable_callback(&usb_device, USB_DEVICE_CALLBACK_SOF);
	usb_device_register_callback(&usb_device, USB_DEVICE_CALLBACK_SUSPEND, USB_Suspend_ISR);
	usb_device_enable_callback(&usb_device, USB_DEVICE_CALLBACK_SUSPEND);
	usb_device_register_callback(&usb_device, USB_DEVICE_CALLBACK_RESET, USB_Suspend_ISR);
	usb_device_enable_callback(&usb_device, USB_DEVICE_CALLBACK_RESET);
	
}

void USB0_Init(void)
{


	udd_enable();

//	USB0_Callback_Init();
	
}

/*
 * \brief Reset the current configuration of the USB device,
 * This routines can be called by UDD when a RESET on the USB line occurs.
 */
/*udc_reset(void)*/

// udi_cdc_putc(88);	// usb write
// udi_cdc_getc();		// usb read