//Vitalii Pidhoretskyi
//PZ-41
//Variant 6 AAI-NO, CMSIS Driver, N=14

#include "stm32f4xx.h"  
#include "flash.h"
#include "stm32f4xx_hal.h"             
#include "Driver_SPI.h"               
#define N 14


uint8_t data[N] = {'V','.','P','I','D','H','O','R','E','T','S','K','Y','I'};
uint8_t readedData[N]={0};
uint8_t status;

extern ARM_DRIVER_SPI Driver_SPI1;
int32_t st;

ARM_DRIVER_SPI* SPI = &Driver_SPI1;

void initSPI (void)
{
	//CS initialization
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIODEN; //enable rcc
	GPIOD->MODER|=0x4000; //set PIN7 out
	GPIOD->ODR |= GPIO_PIN_7;	//SET 1
	
	//spi initialization
	st = SPI->Initialize(NULL);
  st = SPI->PowerControl(ARM_POWER_FULL);
  st = SPI->Control(ARM_SPI_MODE_MASTER | ARM_SPI_CPOL0_CPHA0 | ARM_SPI_MSB_LSB | ARM_SPI_SS_MASTER_UNUSED | ARM_SPI_DATA_BITS(8), 84000000);
}

void SendByte(uint8_t data){
	SPI->Send(&data,1);
}

uint8_t ReceiveByte(void){
	uint8_t data=0x00;
	SPI->Receive(&data,1);
	return data;
}

int main()
{
	initDelay();
	initSPI();
	SetStatus(0);
	status = GetStatus();
	Clear();
	WriteDataArray(0x000000,data,N);
	ReadDataArray(0x000000,readedData,N);
	while(1);
}
