#include "stdint.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "main.h"


extern SPI_HandleTypeDef Spi2Handle;


/****************************
* Send LCD commands 
*****************************/
void command(uint8_t i)
{  

 uint8_t temp1;
 uint8_t temp2;
 uint8_t temp3;
	
	temp1=0x1F;
	temp2= i &(0x0F);
	temp3=(i &(0xF0))>>4;
	
  GPIOI->ODR &= ~GPIO_ODR_ODR_5;    //chip select active low 
	
 while (HAL_SPI_GetState(&Spi2Handle) != HAL_SPI_STATE_READY){}
	 
	 HAL_SPI_Transmit(&Spi2Handle, &temp1, 1, 1000);
	 HAL_SPI_Transmit(&Spi2Handle, &temp2, 1, 1000);
	 HAL_SPI_Transmit(&Spi2Handle, &temp3, 1, 1000);
 
 while (HAL_SPI_GetState(&Spi2Handle) != HAL_SPI_STATE_READY){}
	 
	 GPIOI->ODR |= GPIO_ODR_ODR_5;    // de-assert chip select	 
}

/**
  * write data to the LCD
  */
void data(uint8_t i)
{ 
	uint8_t temp1;
  uint8_t temp2;
  uint8_t temp3;
	
	temp1=0x5F;  
	temp2=i &(0x0F);
	temp3=(i &(0xF0))>>4;
	
	
    GPIOI->ODR &= ~GPIO_ODR_ODR_5;    //chip select active low  
	
    while (HAL_SPI_GetState(&Spi2Handle) != HAL_SPI_STATE_READY){}

		HAL_SPI_Transmit(&Spi2Handle, &temp1, 1, 1000);	
		HAL_SPI_Transmit(&Spi2Handle, &temp2, 1, 1000);
    HAL_SPI_Transmit(&Spi2Handle, &temp3, 1, 1000);			
				
		while (HAL_SPI_GetState(&Spi2Handle) != HAL_SPI_STATE_READY){}
				 
		GPIOI->ODR |= GPIO_ODR_ODR_5;    // de-assert chip select
}

/**
  * Dispaly a string to the LCD
  */
void LCD_I2COutput(uint8_t*aRxBuffer){
	
		int i;
	
		command(0x01);  //clear display
	  command(0x02);  //return home
	
  	while(*aRxBuffer!=NULL){
		  data((0x30) |(*aRxBuffer));
		  aRxBuffer++;
	}
	
	
}

/**
* Dispaly message: "These are my EEPROM Readings: ";
  */
void EEPROM_Output(void){
	
	int j;
	uint8_t length; 
	char *Message="These are my EEPROM Readings: ";
	
	command(0x01);  //clear display	
	command(0x02);  //return home
	 
  length=strlen(Message);
	for (j=0;j<length;j++){
		data(*Message);
		Message++;
	}
	
}
	/**
* Dispaly message: " STARTING COMMS:  PLEASE WAIT...! "  ;
  */
void LCD_Output(void)
{
	int j;	
  uint8_t length; 
	
	char *Message1=" STARTING COMMS:  ";
	char *Message2=" PLEASE WAIT...! ";
	
	command(0x01);  //clear display
	command(0x02);  //return home
	 
  length=strlen(Message1);
	for (j=0;j<length;j++){
		data(*Message1);
		Message1++;
	}
	
	data('\n');
	data('\n');
	
	length=strlen(Message2);
	for (j=0;j<length;j++){
		data(*Message2);
		Message2++;
	}
	
}
	/**
* Initialize LCD  ;
*/
void LCD_Init(void)
{

	  GPIOA->ODR |= GPIO_ODR_ODR_9; 
	  
	  GPIOI->ODR |= GPIO_ODR_ODR_5;    //rest line is always ON

	  command(0x2A);  //function set (extended command set) 
		command(0x71);  //function selection A
	

	  data(0x00);     // disable internal VDD regulator (2.8V I/O). data(0x5C) = enable regulator (5V I/O)

	  command(0x28);  //function set (fundamental command set)
		command(0x08);  //display off, cursor off, blink off
		command(0x2A);  //function set (extended command set)
		command(0x79);  //OLED command set enabled
		command(0xD5);  //set display clock divide ratio/oscillator frequency
		command(0x70);  //set display clock divide ratio/oscillator frequency
		command(0x78);  //OLED command set disabled
		command(0x09);  //extended function set (4-lines)	
		command(0x06);  //COM SEG direction
		command(0x72);  //function selection B

	  data(0x00);  //ROM CGRAM selection
		
		command(0x2A);  //function set (extended command set)
		command(0x79);  //OLED command set enabled
		command(0xDA);  //set SEG pins hardware configuration
		command(0x10);  //set SEG pins hardware configuration
		command(0xDC);  //function selection C
		command(0x00);  //function selection C
		command(0x81);  //set contrast control
		command(0x7F);  //set contrast control
		command(0xD9);  //set phase length
		command(0xF1);  //set phase length
		command(0xDB);  //set VCOMH deselect level
		command(0x40);  //set VCOMH deselect level
		command(0x78);  //OLED command set disabled
		command(0x28);  //function set (fundamental command set)
		command(0x01);  //clear display
		command(0x80);  //set DDRAM address to 0x00
		command(0x0C);  //display ON 
		
		  
    HAL_Delay(5);
		 	 
}