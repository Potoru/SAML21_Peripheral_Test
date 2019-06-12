#ifndef _USB0_H_
#define _USB0_H_

struct usb_module usb_device;

void USB_Suspend_ISR(struct usb_module *module_inst, void* pointer);
void USB_SOF_ISR(struct usb_module *module_inst, void* pointer);
void USB_RESET_ISR(struct usb_module *module_inst, void* pointer);
void USB0_Callback_Init(void);

void USB0_Init(void);



#endif