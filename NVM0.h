#ifndef _NVM0_H_
#define _NVM0_H_

#define NVM_SAML21J18B_BYTE_SIZE 8192
#define NVM_START_ADDRESS 0x00400000
#define NVM_END_ADDRESS (NVM_START_ADDRESS+NVM_SAML21J18B_SIZE)
#define NVM_PAGE_SIZE 64
#define NVM_PAGE_IN_ROW 4

uint16_t NVM_Address_Position;

void NVM_Init(void);
void NVM_Single_Data_Write(void);
void NVM_Single_Data_Read(void);
void ex(void);
#endif