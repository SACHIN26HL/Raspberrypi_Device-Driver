#ifndef BCM2837_H
#define BCM2837_H


//raspberry pi 3 Register or GPIO address

#define GPIO_BASE_ADD 0x7E200000

/*........ Physical Address.....*/
#define GPIO_FSELE0 0x7E200000               //size 32  and R/W  0-9
#define GPIO_FSELE1 0x7E200004				 //GPIO Select function 1
#define GPIO_FSELE2 0x7E200008				 // Gpio select function 2	
#define GPIO_FSELE3 0x7E20000C				 // Gpio select function 3
#define GPIO_FSELE4 0x7E200010
#define GPIO_FSELE5 0x7E200014				 // Gpio select function 5

#define GPIO_PIN_OUTPUT_SET0 0x7E20001C      //GPIO PIN output set 0
#define GPIO_PIN_OUTPUT_SET1 0x7E200020		 //GPOIO PIN output set 1

#define GPIO_PIN_OUTPUT_CLR0 0x7E200028      //GPIO PIN output clear 0
#define GPIO_PIN_OUTPUT_CLR1 0x7E20002C      //GPIO pin output clear 1

#define GPIO_PIN_LEVEL0 0x7E200034			 //Gpio Pin level 0
#define GPIO_PIN_LEVEL1 0x7E200038			 //GPIO pin level 1 



/* offset values */
#define GPIO_FSELE0_OFFVALUE 0x00                //size 32  and R/W  0-9
#define GPIO_FSELE1_OFFVALUE 0x04				 //GPIO Select function 1
#define GPIO_FSELE2_OFFVALUE 0x08				 // Gpio select function 2	
#define GPIO_FSELE3_OFFVALUE 0x0C				 // Gpio select function 3
#define GPIO_FSELE4_OFFVALUE 0x10
#define GPIO_FSELE5_OFFVALUE 0x14				 // Gpio select function 5

#define GPIO_PIN_OUTPUT_SET0_OFFVALUE 0x1C       //GPIO PIN output set 0
#define GPIO_PIN_OUTPUT_SET1_OFFVALUE 0x20		 //GPOIO PIN output set 1

#define GPIO_PIN_OUTPUT_CLR0_OFFVALUE 0x28       //GPIO PIN output clear 0
#define GPIO_PIN_OUTPUT_CLR1_OFFVALUE 0x2C       //GPIO pin output clear 1

#define GPIO_PIN_LEVEL0_OFFVALUE 0x34			 //Gpio Pin level 0
#define GPIO_PIN_LEVEL1_OFFVALUE 0x38			 //GPIO pin level 1 



#endif
