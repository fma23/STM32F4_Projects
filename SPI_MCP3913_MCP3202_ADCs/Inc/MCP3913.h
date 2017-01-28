#ifndef __MCP3913_h
#define __MCP3913_h


#include "stdint.h"


typedef union
{ 
    struct
    {
			  unsigned char DRSTATUS:6;				      // bit 5-0 Data ready status bit for each individual ADC channel, DRSTATUS<n> = 1 - Channel CHn data is not ready (DEFAULT)
        unsigned char Unimplemented:6;				// bit 11-6 : Read as 0                                     // DRSTATUS<n> = 0 - Channel CHn data is ready. The status bit is set back to '1' after reading the 
        unsigned char Reserved:2;             // bit 13-12 Should be kept equal to 0 at all times
			  unsigned char EN_INT:1;               // bit 14: Enable for the CRCREG interrupt function
		    unsigned char EN_CRCCOM:1;				    //bit 15: Enable CRC CRC-16 Checksum on Serial communications
			  unsigned char WIDTH_DATA:2;			      //bit 17-16:Data Ready Link Control; 01 = 24-bit (default)
			  unsigned char WIDTH_CRC:1;			      //bit 18: Width setting for CRC word: 0 for 16 bit (default)
			  unsigned char WDR_LINK:1;			        //bit 19 Data Ready Link Control
			  unsigned char DR_HIZ:1;			          //bit 20: Data Ready Pin Inactive State Control 
			  unsigned char WRITE:1;				        //bit 21: Address counter increment setting for Write Communication
			  unsigned char READ:2;                 //bit 22-23 Address counter increment setting for Read Communication
		
		} bits;
    unsigned int     StatcomRegi_val;       	//register access

} STATUSCOM_Register;



typedef union
{ 
    struct
    {
			  unsigned char VREFCAL:8;				      //bit 7-0: Internal Voltage Temperature coefficient VREFCAL<7:0> value
			  unsigned char Unimplemented:5;				//bit 12-8 : Read as 0
			  unsigned char OSR:3;                  //bit 15-13  Should be kept equal to 0 at all times
        unsigned char PRE:2;                  //bit 17-16: Analog Master Clock (AMCLK) Prescaler Value
			  unsigned char BOOST:2;				        //bit 19-18:  Bias Current Selection for all ADCs 
			  unsigned char DITHER:2;			          //bit 21-20:  Control for dithering circuit for idle tone’s cancellation and improved THD on all channels
			  unsigned char EN_GAINCAL:1;			      //bit 22: Enables or disables the 24-bit digital gain error calibration on all channels
			  unsigned char EN_OFFCAL:1;			      //bit 23: Enables the 24-bit digital offset error calibration on all channels
			
    } bits;
    unsigned int     Config0Regi_val;       		      //register access

} CONFIG0_Register;

typedef union
{ 
    struct
    {
			  unsigned char Unimplemented3:6;				//bit 5-0: Read as 0
        unsigned char CLKEXT:1;				        //bit 6 : Crystal oscillator enabled. A crystal must be placed between OSC1 and OSC2 with proper decocapacitors. The digital power consumption (DI
        unsigned char VREFEXT:1;              //bit 7 :Internal Voltage Reference selection bit                                     // ) is increased in this mode due to the oscillator.DD                                     
			  unsigned char SHUTDOWN:6;             //bit 13-8 : Shutdown Mode setting for each individual ADC
			  unsigned char Unimplemented2:2;				//bit 15-14 Read as 0
			  unsigned char RESET:6;			          //bit 21-16: Soft Reset mode setting for each individual ADC
			  unsigned char Unimplemented1:2;		    //bit 23-22 : Read as 0
			
    } bits;
    unsigned int     Config1Regi_val;         //register access

} CONFIG1_Register;


/**Function Declartions **/

void MCP3913A_ReadRequest(uint8_t *address);
void MCP3913A_ReadAdc(uint8_t *address);
void MCP3913Config0Reg(void);
void MCP3913Config1Reg(void);
void MCP3913StatusComReg(void);
void MCP3913_Configuration(void);
void MCP3204_ReadRequest(uint8_t address); 

 #endif
