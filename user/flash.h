#ifndef FLASH_H
#define FLASH_H

#include "stm32f4xx_hal.h"             
 
//Device Operation Instructions
#define WRITE_STATUS_REGISTER 0x01
#define BYTE_PROGRAM 0x02
#define READ_INSTUCTION 0x03
#define WRITE_DISABLE 0x04
#define READ_STATUS_REGISTER 0x05
#define WRITE_ENABLE 0x06
#define ENABLE_WRITE_STATUS_REGISTER 0x50
#define FULL_MEMORY_ERASE_INSTUCTION 0x60


void initDelay(void);
void DelayMs(uint32_t ms);
void SendByte(uint8_t);
uint8_t ReceiveByte(void);

void ReadDataArray(uint32_t,uint8_t*,uint16_t);
uint8_t GetStatus(void);
void WriteDataArray(uint32_t,uint8_t*,uint8_t);
void WaitUntilBusy(void);
void SetStatus(uint8_t);
void DisableWrite(void);
void EnableWrite(void);
void WriteByte(uint32_t,uint8_t);

void ClearSector(uint32_t);
void Clear(void);
void setAddress(uint32_t);


#endif
