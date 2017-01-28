#include "main.h"
#include "MCP3913.h"



/* =================================================================== */
              /*MCP3913 and MCP3204 Gloabal Variables */           
/* =================================================================== */
volatile uint8_t ADCCh0[3]={0}; 
volatile uint8_t ADCCh1[3]={0};
volatile uint8_t ADCCh2[3]={0};
volatile uint8_t ADCCh3[3]={0};
volatile uint8_t ADCCh4[3]={0};
volatile uint8_t ADCCh5[3]={0};

uint8_t ADC3204Data_Ch0[3]={0};
uint8_t ADC3204Data_Ch1[3]={0};
uint8_t ADC3204Data_Ch2[3]={0};
uint8_t ADC3204Data_Ch3[3]={0};
 
volatile uint8_t ADC3913StatusComm_Reg[3]={0}; 
volatile uint8_t ADC3913Config0_Reg[3]={0};
volatile uint8_t ADC3913Config1_Reg[3]={0};
volatile uint8_t ADC3913LOCK_Reg[3]={0};


volatile CONFIG0_Register ADC_Config0;
volatile CONFIG1_Register ADC_Config1;
volatile STATUSCOM_Register ADC_StatusCom;
volatile uint8_t Reg_Address; 

extern volatile uint8_t ADCData[100][3];

uint8_t ADC3913Data[3]={0}; 
 

extern SPI_HandleTypeDef Spi3Handle;


void MCP3913Config0Reg(void){
	
	uint8_t Config0Reg_ContByte=0; 
	uint8_t Config0DataByteBuffer[3]={0};
	
	ADC_Config0.Config0Regi_val=0;         // init bit field to 0
	
	ADC_Config0.bits.PRE=3;                // "10"  AMCLK = MCLK/4
	ADC_Config0.bits.OSR=5;                // "001"   001 = 64 (fd= 15.625 ksps for MCLK = 4 MHz, f=AMCLK=1MHz)
	ADC_Config0.bits.EN_OFFCAL=0;          // DEFAULT
	ADC_Config0.bits.EN_GAINCAL=0;         // DEFAULT
	ADC_Config0.bits.DITHER= 3;            // Dithering ON, Strength = Maximum (DEFAULT)
  ADC_Config0.bits.BOOST=2;              // All channels have current x 1 (Default)
	ADC_Config0.bits.VREFCAL=0x50;         // Default value
	
	Config0Reg_ContByte= 0x5A;             // Device address"01"+Register address: 0x0D +RW: 0 for write, 1 for read
	
	Config0DataByteBuffer[0]=ADC_Config0.Config0Regi_val >>16;
	Config0DataByteBuffer[1]=ADC_Config0.Config0Regi_val >>8;
	Config0DataByteBuffer[2]=ADC_Config0.Config0Regi_val;
			
  GPIOC->ODR &=  ~GPIO_ODR_ODR_7; // de-assert CS for MCP3913
	
	while (HAL_SPI_GetState(&Spi3Handle) != HAL_SPI_STATE_READY){}
	
	HAL_SPI_Transmit(&Spi3Handle, &Config0Reg_ContByte, 1, 1000); //transmit contro byte

		
	while (HAL_SPI_GetState(&Spi3Handle) != HAL_SPI_STATE_READY){}
	HAL_SPI_Transmit(&Spi3Handle, &Config0DataByteBuffer[0], 1, 1000); //transmit control byte
  HAL_SPI_Transmit(&Spi3Handle, &Config0DataByteBuffer[1], 1, 1000); //transmit control byte
	HAL_SPI_Transmit(&Spi3Handle, &Config0DataByteBuffer[2], 1, 1000); //transmit control byte
  
  GPIOC->ODR |=  GPIO_ODR_ODR_7; // Assert CS for MCP3913

}

void MCP3913Config1Reg(void){
	
	uint8_t Config1Reg_ContByte=0; 
	uint8_t Config1DataByteBuffer[3]={0};
	
	ADC_Config1.Config1Regi_val=0;           // init bit field to 0
	
	ADC_Config1.bits.Unimplemented3= 0;      //Default reads as 0
	ADC_Config1.bits.CLKEXT=0;               //use external crystal 
	ADC_Config1.bits.VREFEXT=0;              //use internal Vref
	ADC_Config1.bits.SHUTDOWN=0;             //ADC channels are not shutdown
	ADC_Config1.bits.Unimplemented2=0;       //Default reads as 0
	ADC_Config1.bits.RESET=0x00;             //ADC Channels not in software reset
  ADC_Config1.bits.Unimplemented2=0;       //Default reads as 0

	Config1Reg_ContByte= 0x5C;               //(0x0E)|(0x20);  //0101 1100 device address"01"+Register; address: 0E+RW: 0 for write, 1 for read

	Config1DataByteBuffer[0]=ADC_Config1.Config1Regi_val >>16;
	Config1DataByteBuffer[1]=ADC_Config1.Config1Regi_val >>8;
	Config1DataByteBuffer[2]=ADC_Config1.Config1Regi_val;
	
	GPIOC->ODR &=  ~GPIO_ODR_ODR_7; // de-assert CS for MCP3913
	
	while (HAL_SPI_GetState(&Spi3Handle) != HAL_SPI_STATE_READY){}
	
	HAL_SPI_Transmit(&Spi3Handle, &Config1Reg_ContByte, 1, 1000); //transmit contro byte
	HAL_SPI_Transmit(&Spi3Handle, &Config1DataByteBuffer[0], 1, 1000);   //transmit data byte1 
  HAL_SPI_Transmit(&Spi3Handle, &Config1DataByteBuffer[1], 1, 1000);   //transmit data byte1 
	HAL_SPI_Transmit(&Spi3Handle, &Config1DataByteBuffer[2], 1, 1000);   //transmit data byte1 	
	
	while (HAL_SPI_GetState(&Spi3Handle) != HAL_SPI_STATE_READY){}
	
   GPIOC->ODR |=  GPIO_ODR_ODR_7; // Assert CS for MCP3913
}


void MCP3913StatusComReg(void){
	
	uint8_t StatusComReg_ContByte=0; 
	uint8_t StatusComDataByteBuffer[3]={0};
	
	ADC_StatusCom.StatcomRegi_val=0; 
	
	ADC_StatusCom.bits.DRSTATUS=0x3F;      //DRSTATUS<5:0>: Data ready status bit for each individual ADC channel
																				 //DRSTATUS<n> = 1 - Channel CHn data is not ready (DEFAULT)
																				 //DRSTATUS<n> = 0 - Channel CHn data is ready. The status bit is set back to '1' after reading the 
																				 //STATUSCOM register. The status bit is not set back to '1' by the read of the corresponding channel
																				 //ADC data.
	ADC_StatusCom.bits.Unimplemented=0;    //Read as 0 
	ADC_StatusCom.bits.Reserved=0 ;        //Should be kept equal to 0 at all times
	ADC_StatusCom.bits.EN_INT=0;           //Enable for the CRCREG interrupt function; disabled for default   
	ADC_StatusCom.bits.EN_CRCCOM=0;        //Disabled (Default)
	ADC_StatusCom.bits.WIDTH_DATA=1;       //24-bit (default)
	ADC_StatusCom.bits.WIDTH_CRC=0;        //16 bit (default)
	ADC_StatusCom.bits.WDR_LINK=1;         //1:Data Ready link disabled, only one pulse is generared for all ADC channels. 0: Each ADC produces its own data ready pulse on the DR pin.
	ADC_StatusCom.bits.DR_HIZ=0;           //1: The DR pin state is a logic high when data is NOT ready. 0: The DR pin state is high-impedance when data is NOT ready (DEFAULT)
  ADC_StatusCom.bits.WRITE=0;            //0: Address not incremented, continually writes to the same single register address
	                                        //1:Address counter auto-increments and loops on writable part of the register map (DEFAULT)
	ADC_StatusCom.bits.READ=0;             //0: Read same register; Address counter auto-increments, loops on register TYPES (DEFAULT)
	

	StatusComReg_ContByte=  0x58;          //0101 1000 device address"01"+Register address: 0x0C +RW: 0 for write, 1 for read
	
	StatusComDataByteBuffer[0]=ADC_StatusCom.StatcomRegi_val >>18;
	StatusComDataByteBuffer[1]=ADC_StatusCom.StatcomRegi_val >>8;
	StatusComDataByteBuffer[2]=ADC_StatusCom.StatcomRegi_val;
	
	 GPIOC->ODR &=  ~GPIO_ODR_ODR_7; // Assert CS for MCP3913
	
	while (HAL_SPI_GetState(&Spi3Handle) != HAL_SPI_STATE_READY){}
	
	HAL_SPI_Transmit(&Spi3Handle, &StatusComReg_ContByte, 1, 1000); //transmit control byte
	HAL_SPI_Transmit(&Spi3Handle, &StatusComDataByteBuffer[0], 1, 1000);   //transmit data byte1 
  HAL_SPI_Transmit(&Spi3Handle, &StatusComDataByteBuffer[1], 1, 1000);   //transmit data byte1 
	HAL_SPI_Transmit(&Spi3Handle, &StatusComDataByteBuffer[2], 1, 1000);   //transmit data byte1 	
	 
  while (HAL_SPI_GetState(&Spi3Handle) != HAL_SPI_STATE_READY){}
 
  GPIOC->ODR |=  GPIO_ODR_ODR_7; // Assert CS for MCP3913
}

void MCP3913A_ReadRequest(uint8_t *address)
{
	 
		*address= *address<<1;
	  *address|=1<<0; 
	  *address=*address| 0x40;
	
	  GPIOC->ODR &=  ~GPIO_ODR_ODR_7; // Assert CS for MCP3913

    while (HAL_SPI_GetState(&Spi3Handle) != HAL_SPI_STATE_READY){}
		
	  HAL_SPI_Transmit(&Spi3Handle, address, 1, 1000); //transmit control byte for corresponding ADC channel 
		
	  while (HAL_SPI_GetState(&Spi3Handle) != HAL_SPI_STATE_READY){}

		MCP3913A_ReadAdc(address); 
}


void MCP3913A_ReadAdc(uint8_t *address){
	
	uint8_t ADCDataBytes[3]={0};
	uint8_t i= 0;
	
	 GPIOC->ODR &=  ~GPIO_ODR_ODR_7; // De-assert CS for MCP3913

	while (HAL_SPI_GetState(&Spi3Handle) != HAL_SPI_STATE_READY){}

	HAL_SPI_Receive(&Spi3Handle, ADCDataBytes, 3, 100);

  if(*address==0x41)   // Read Channel 0
	{
			for(i=0; i<3;i++){
				ADCCh0[i]=ADCDataBytes[i]; 
			}
  }
  else if(*address==0x43)  // Read Channel 1
	{

	  for(i=0; i<3;i++){
				ADCCh1[i]=ADCDataBytes[i]; 			
	  }
	}
	
  else if(*address==0x45)   // Read Channel 2
	{
			for(i=0; i<3;i++){
				ADCCh2[i]=ADCDataBytes[i]; 
			}
  }
	else if(*address==0x47)   // Read Channel 3
	{
			for(i=0; i<3;i++){
				ADCCh3[i]=ADCDataBytes[i]; 
			}
  }
	else if(*address==0x49)   // Read Channel 4
	{
			for(i=0; i<3;i++){
				ADCCh4[i]=ADCDataBytes[i]; 
			}
  }
	else if(*address==0x4B)  // Read Channel 5
	{
			for(i=0; i<3;i++){
				ADCCh5[i]=ADCDataBytes[i]; 
			}
  }

	else if(*address==0x59)  // Read Status Comm register
	{
			for(i=0; i<3;i++){
				ADC3913StatusComm_Reg[i]=ADCDataBytes[i]; 
			}
  }
  else if(*address==0x5B)  // Read Status Comm register
	{
			for(i=0; i<3;i++){
				ADC3913Config0_Reg[i]=ADCDataBytes[i]; 
			}
  }
	 else if(*address==0x5D)  // Read Status Comm register
	{
			for(i=0; i<3;i++){
				ADC3913Config1_Reg[i]=ADCDataBytes[i]; 
			}
  }
	else if(*address==0x7F) // Read Status Comm register
	{
			for(i=0; i<3;i++){
				ADC3913LOCK_Reg[i]=ADCDataBytes[i]; 
			}
  }
	
}


void MCP3913_Configuration(void)
{
	
 GPIOF->ODR &= ~ GPIO_ODR_ODR_11; // Reset MCP3913;
 
 HAL_Delay(2);  // wait 2 ms
	
 GPIOF->ODR |=  GPIO_ODR_ODR_11; // Toggle Reset line for MCP3913;
 GPIOF->ODR |=  GPIO_ODR_ODR_14; // set CS line high for MCP3913;
 GPIOF->ODR |=  GPIO_ODR_ODR_15; // set CS line high for MCP3204;
	
 MCP3913Config0Reg();   //configure register0 of MCP3913
 MCP3913Config1Reg();   //configure register1 of MCP3913
 MCP3913StatusComReg();  //configure StatusComm of MCP3913
}
void MCP3204_ReadRequest(uint8_t address){
	
	uint8_t i=0;
  uint8_t RegisterAddressBuff[3]={0};
	
	RegisterAddressBuff[0]=0x06;
	RegisterAddressBuff[1]= address<<6;
	RegisterAddressBuff[2]=0;
	
	GPIOC->ODR |=  GPIO_ODR_ODR_7;            // set chip select PC7 for MCP3913
	GPIOC->ODR |=  GPIO_ODR_ODR_9;            // set chip select PC9 for MCP3204
	
	GPIOC->ODR &=  ~GPIO_ODR_ODR_9;           // de-assert chip select line PC9 for MCP3204

	
	while (HAL_SPI_GetState(&Spi3Handle) != HAL_SPI_STATE_READY){}
	
  if(address==0x00)
	{		
	HAL_SPI_TransmitReceive(&Spi3Handle, &RegisterAddressBuff[0], &ADC3204Data_Ch0[0],3, 1000);
	}
	else if(address==0x01)
	{		
	HAL_SPI_TransmitReceive(&Spi3Handle, &RegisterAddressBuff[0], &ADC3204Data_Ch1[0],3, 1000);
	}
	else if(address==0x02)
	{		
	HAL_SPI_TransmitReceive(&Spi3Handle, &RegisterAddressBuff[0], &ADC3204Data_Ch2[0],3, 1000);
	}
	else if(address==0x03)
	{		
	HAL_SPI_TransmitReceive(&Spi3Handle, &RegisterAddressBuff[0], &ADC3204Data_Ch3[0],3, 1000);
	}
	
	GPIOC->ODR |=  GPIO_ODR_ODR_9;            // set chip select PC9 for MCP3204                     
}