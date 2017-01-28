#include "main.h"



void Configure_LEDs(void) 
{
	/* Enable both GPIO clock */
	__GPIOF_CLK_ENABLE();
  __GPIOG_CLK_ENABLE();
	__GPIOI_CLK_ENABLE();
	__GPIOA_CLK_ENABLE();
	
	/* Select output mode (01) on PA10: for I2C_RW */
	GPIOA->MODER  &= ~(3UL << 2 * 10);
  GPIOA->MODER  |=  (1UL << 2 * 10);
  GPIOA->OTYPER &= ~(1UL <<     10);
	GPIOA->MODER = (GPIOA->MODER & ~(GPIO_MODER_MODER10)) | (GPIO_MODER_MODER10_0);  //I2C_RW 
	


	/* Select output mode (01) on PI9: for the Green LED*/
	GPIOI->MODER  &= ~(3UL << 2 * 9);
  GPIOI->MODER  |=  (1UL << 2 * 9);
  GPIOI->OTYPER &= ~(1UL <<     9);
	GPIOI->MODER = (GPIOI->MODER & ~(GPIO_MODER_MODER9)) | (GPIO_MODER_MODER9_0); 
	
	/* Select output mode (01) on PG0: for the BATT HIGH*/    
	GPIOG->MODER  &= ~(3UL << 2 * 0);
  GPIOG->MODER  |=  (1UL << 2 * 0);
  GPIOG->OTYPER &= ~(1UL <<     0);
	GPIOG->MODER = (GPIOG->MODER & ~(GPIO_MODER_MODER0)) | (GPIO_MODER_MODER0_0); 
	
		/* Select output mode (01) on PG1: for the BATT OK*/    
	GPIOG->MODER  &= ~(3UL << 2 * 1);
  GPIOG->MODER  |=  (1UL << 2 * 1);
  GPIOG->OTYPER &= ~(1UL <<     1);
	GPIOG->MODER = (GPIOG->MODER & ~(GPIO_MODER_MODER1)) | (GPIO_MODER_MODER1_0); 
	
	
		/* Select output mode (01) on PG2: for the BATT LOW*/    
	GPIOG->MODER  &= ~(3UL << 2 * 2);
  GPIOG->MODER  |=  (1UL << 2 * 2);
  GPIOG->OTYPER &= ~(1UL <<     2);
	GPIOG->MODER = (GPIOG->MODER & ~(GPIO_MODER_MODER2)) | (GPIO_MODER_MODER2_0); 
	
	
	/* Select output mode (01) on PG9: for the BUZZER*/    
	GPIOG->MODER  &= ~(3UL << 2 * 9);
  GPIOG->MODER  |=  (1UL << 2 * 9);
  GPIOG->OTYPER &= ~(1UL <<     9);
	GPIOG->MODER = (GPIOG->MODER & ~(GPIO_MODER_MODER9)) | (GPIO_MODER_MODER9_0); 
	
	
	
	/* Select output mode (01) on PF3: AC OK*/    
	GPIOF->MODER  &= ~(3UL << 2 * 3);
  GPIOF->MODER  |=  (1UL << 2 * 3);
  GPIOF->OTYPER &= ~(1UL <<     3);
	GPIOF->MODER = (GPIOF->MODER & ~(GPIO_MODER_MODER3)) | (GPIO_MODER_MODER3_0);
	
		/* Select output mode (01) on PF4: AC FAIL*/    
	GPIOF->MODER  &= ~(3UL << 2 * 4);
  GPIOF->MODER  |=  (1UL << 2 * 4);
  GPIOF->OTYPER &= ~(1UL <<     4);
	GPIOF->MODER = (GPIOF->MODER & ~(GPIO_MODER_MODER4)) | (GPIO_MODER_MODER4_0);
	
	/* Select output mode (01) on PF5: REC OK*/    
	GPIOF->MODER  &= ~(3UL << 2 * 5);
  GPIOF->MODER  |=  (1UL << 2 * 5);
  GPIOF->OTYPER &= ~(1UL <<     5);
	GPIOF->MODER = (GPIOF->MODER & ~(GPIO_MODER_MODER5)) | (GPIO_MODER_MODER5_0);
	
		/* Select output mode (01) on PF6: REC FAIL*/    
	GPIOF->MODER  &= ~(3UL << 2 * 6);
  GPIOF->MODER  |=  (1UL << 2 * 6);
  GPIOF->OTYPER &= ~(1UL <<     6);
	GPIOF->MODER = (GPIOF->MODER & ~(GPIO_MODER_MODER6)) | (GPIO_MODER_MODER6_0);
	
		/* Select output mode (01) on PF7: REC OVLD*/    
	GPIOF->MODER  &= ~(3UL << 2 * 7);
  GPIOF->MODER  |=  (1UL << 2 * 7);
  GPIOF->OTYPER &= ~(1UL <<     7);
	GPIOF->MODER = (GPIOF->MODER & ~(GPIO_MODER_MODER7)) | (GPIO_MODER_MODER7_0);
	

/* Select output mode (01) on PF8: for POS FAULT*/    
	GPIOF->MODER  &= ~(3UL << 2 * 8);
  GPIOF->MODER  |=  (1UL << 2 * 8);
  GPIOF->OTYPER &= ~(1UL <<     8);
	GPIOF->MODER = (GPIOF->MODER & ~(GPIO_MODER_MODER8)) | (GPIO_MODER_MODER8_0);
	
	/* Select output mode (01) on PF9: for NEG FAULT*/    
	GPIOF->MODER  &= ~(3UL << 2 * 9);
  GPIOF->MODER  |=  (1UL << 2 * 9);
  GPIOF->OTYPER &= ~(1UL <<     9);
	GPIOF->MODER = (GPIOF->MODER & ~(GPIO_MODER_MODER9)) | (GPIO_MODER_MODER9_0);
	
	/* Select output mode (01) on PF10: for the DC OUTPUT*/    
	GPIOF->MODER  &= ~(3UL << 2 * 10);
  GPIOF->MODER  |=  (1UL << 2 * 10);
  GPIOF->OTYPER &= ~(1UL <<     10);
	GPIOF->MODER = (GPIOF->MODER & ~(GPIO_MODER_MODER10)) | (GPIO_MODER_MODER10_0); 
	
	/* Select output mode (01) on PF11: for EQUILIZE GREEN LED */    
	GPIOF->MODER  &= ~(3UL << 2 * 11);
  GPIOF->MODER  |=  (1UL << 2 * 11);
  GPIOF->OTYPER &= ~(1UL <<     11);
	GPIOF->MODER = (GPIOF->MODER & ~(GPIO_MODER_MODER11)) | (GPIO_MODER_MODER11_0); 
	
		/* Select output mode (01) on PF12: for EQUILIZE GREEN LED*/    
	GPIOF->MODER  &= ~(3UL << 2 * 12);
  GPIOF->MODER  |=  (1UL << 2 * 12);
  GPIOF->OTYPER &= ~(1UL <<     12);
	GPIOF->MODER = (GPIOF->MODER & ~(GPIO_MODER_MODER12)) | (GPIO_MODER_MODER12_0);
	
		/* Select output mode (01) on PF13: for SHUNT TRIP RED LED*/    
	GPIOF->MODER  &= ~(3UL << 2 * 13);
  GPIOF->MODER  |=  (1UL << 2 * 13);
  GPIOF->OTYPER &= ~(1UL <<     13);
	GPIOF->MODER = (GPIOF->MODER & ~(GPIO_MODER_MODER13)) | (GPIO_MODER_MODER13_0);
	
		/* Select output mode (01) on PF14: for SHUNT TRIP RED LED*/    
	GPIOF->MODER  &= ~(3UL << 2 * 14);
  GPIOF->MODER  |=  (1UL << 2 * 14);
  GPIOF->OTYPER &= ~(1UL <<     14);
	GPIOF->MODER = (GPIOF->MODER & ~(GPIO_MODER_MODER14)) | (GPIO_MODER_MODER14_0);
	
	/* Select output mode (01) on PF15: for the COMMON ALARM*/    
	GPIOF->MODER  &= ~(3UL << 2 * 15);
  GPIOF->MODER  |=  (1UL << 2 * 15);
  GPIOF->OTYPER &= ~(1UL <<     15);
	GPIOF->MODER = (GPIOF->MODER & ~(GPIO_MODER_MODER15)) | (GPIO_MODER_MODER15_0); 

}