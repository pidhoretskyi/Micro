#include "flash.h"

uint32_t msTicks;
 
void FlashOff(void)
{
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_7,GPIO_PIN_SET);
}
void FlashOn(void)
{
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_7,GPIO_PIN_RESET);
}


void WriteByte(uint32_t address,uint8_t data){	
	EnableWrite();
	DelayMs(50);
  FlashOn();
  SendByte(BYTE_PROGRAM);
  setAddress(address);
  SendByte(data);
  FlashOff();
  WaitUntilBusy();
}

void setAddress(uint32_t addr){
	SendByte(addr >> 16);
  SendByte(addr >> 8);  
  SendByte(addr);
}

uint8_t GetStatus(void){
	uint8_t data = 0;
	FlashOn();
  SendByte(READ_STATUS_REGISTER);
  data = ReceiveByte();
  FlashOff();
	return data;
}

void WaitUntilBusy(void){
  while (1)
  {
    if ((GetStatus()&0x01)!=0x01) break;
    DelayMs(50);
  }
}

void SetStatus(uint8_t statusData){
	FlashOn();
	SendByte(ENABLE_WRITE_STATUS_REGISTER);	
	FlashOff();
	FlashOn();
	SendByte(WRITE_STATUS_REGISTER);
	SendByte(statusData);
	FlashOff();
}

void DisableWrite(void){
	FlashOn();
  SendByte(WRITE_DISABLE);
  FlashOff();
}

void EnableWrite(void){
	FlashOn();
  SendByte(WRITE_ENABLE);
  FlashOff();
}



void WriteDataArray(uint32_t address,uint8_t* data,uint8_t len){
	for(uint16_t i=0;i<len;i++){
		WriteByte(address+i,data[i]);
	}
}

void ReadDataArray(uint32_t address,uint8_t* dest,uint16_t count){
	FlashOn();
	SendByte(READ_INSTUCTION);
	setAddress(address);
	for(uint16_t i=0;i<count;i++){ 
		dest[i]=ReceiveByte();
	}
	FlashOff();
}

void Clear(void){
	EnableWrite();
  DelayMs(50);
  FlashOn();
  SendByte(FULL_MEMORY_ERASE_INSTUCTION);
  FlashOff();
  WaitUntilBusy();
  DelayMs(50);
}

void SysTick_Handler()
{
    if (msTicks != 0)msTicks--;
}
 
void initDelay()
{
    SystemCoreClockUpdate();
    SysTick_Config(SystemCoreClock / 1000);
}
 
void DelayMs(uint32_t ms)
{
  msTicks = ms;  
	while(msTicks);
}
