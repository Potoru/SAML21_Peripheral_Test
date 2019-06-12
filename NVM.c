/*
시퀀스 설명 : 
NVM Unlock
지울 어드레스의 데이터를 지움
해당 어드레스에 데이터 입력
NVM Lock

SAML의 사용 가능한 어드레스는 0x00804000 부터 

*/


#include "ALL_HEADER.h"

void NVM_Init(void)
{
	struct nvm_config NVM_Config0;
	
	nvm_get_config_defaults(&NVM_Config0);
	NVM_Config0.manual_page_write = false;
		
	while(nvm_set_config(&NVM_Config0) != STATUS_OK);

}

void NVM_Single_Data_Write()
{
	uint32_t NVM_Address = NVM_START_ADDRESS+(NVM_PAGE_SIZE * NVM_Address_Position);
	uint8_t page_buffer[NVM_PAGE_SIZE];
	for (uint32_t i = 0; i < NVM_PAGE_SIZE; i++) {
		page_buffer[i] = i;
	}
	enum status_code error_code;
	do
	{
		error_code = nvm_erase_row(NVM_Address);
	} while (error_code == STATUS_BUSY);
	do
	{
		error_code = nvm_write_buffer(NVM_Address, page_buffer, NVM_PAGE_SIZE);
	} while (error_code == STATUS_BUSY);
}

void NVM_Single_Data_Read()
{
	uint32_t NVM_Address = NVM_START_ADDRESS+(NVM_PAGE_SIZE*NVM_Address_Position);
	uint8_t page_buffer[NVM_PAGE_SIZE] = {0, };
	enum status_code error_code;
	do
	{
		error_code = nvm_read_buffer(NVM_Address, page_buffer, NVM_PAGE_SIZE);
	} while (error_code != STATUS_OK);		for(uint8_t i = 0; i <= NVM_PAGE_SIZE; i++)	{		printf("%d : %d\r\n", i, page_buffer[i]);	}
}


void ex()
{
	uint8_t page_buffer[NVMCTRL_PAGE_SIZE];
	for (uint32_t i = 0; i < NVMCTRL_PAGE_SIZE; i++) {
		page_buffer[i] = i;
	}
	enum status_code error_code;
	do
	{
		error_code = nvm_erase_row(
		100 * NVMCTRL_ROW_PAGES * NVMCTRL_PAGE_SIZE);
	} while (error_code == STATUS_BUSY);
	do
	{
		error_code = nvm_write_buffer(
		100 * NVMCTRL_ROW_PAGES * NVMCTRL_PAGE_SIZE,
		page_buffer, NVMCTRL_PAGE_SIZE);
	} while (error_code == STATUS_BUSY);
	do
	{
		error_code = nvm_read_buffer(
		100 * NVMCTRL_ROW_PAGES * NVMCTRL_PAGE_SIZE,
		page_buffer, NVMCTRL_PAGE_SIZE);
	} while (error_code == STATUS_BUSY);		for(uint8_t i = 0; i <= NVMCTRL_PAGE_SIZE; i++)	{		printf("%d : %d\r\n", i, page_buffer[i]);	}}