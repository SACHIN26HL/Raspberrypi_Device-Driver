/***************************************************************************//**
*  \file       user_application.c
*
*  \details    Userspace application to test the Device driver
*
*   \Tested with Linux raspberrypi 5.10.27-v7l-embetronicx-custom+
*
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdint.h>


//raspberry pi 3 Register or GPIO address

#define GPIO_BASE_ADD 0x7E200000

/*........ Physical Address.....*/
#define GPIO_FSELE0 0x7E200000               //size 32  and R/W  0-9
#define GPIO_FSELE1 0x7E200004                           //GPIO Select function 1
#define GPIO_FSELE2 0x7E200008                           // Gpio select function 2      
#define GPIO_FSELE3 0x7E20000C                           // Gpio select function 3
#define GPIO_FSELE4 0x7E200010
#define GPIO_FSELE5 0x7E200014                           // Gpio select function 5

#define GPIO_PIN_OUTPUT_SET0 0x7E20001C      //GPIO PIN output set 0
#define GPIO_PIN_OUTPUT_SET1 0x7E200020          //GPOIO PIN output set 1

#define GPIO_PIN_OUTPUT_CLR0 0x7E200028      //GPIO PIN output clear 0
#define GPIO_PIN_OUTPUT_CLR1 0x7E20002C      //GPIO pin output clear 1

#define GPIO_PIN_LEVEL0 0x7E200034                       //Gpio Pin level 0
#define GPIO_PIN_LEVEL1 0x7E200038                       //GPIO pin level 1 



/* offset values */
#define GPIO_FSELE0_OFFVALUE 0x00                //size 32  and R/W  0-9
#define GPIO_FSELE1_OFFVALUE 0x04                                //GPIO Select function 1
#define GPIO_FSELE2_OFFVALUE 0x08                                // Gpio select function 2      
#define GPIO_FSELE3_OFFVALUE 0x0C                                // Gpio select function 3
#define GPIO_FSELE4_OFFVALUE 0x10
#define GPIO_FSELE5_OFFVALUE 0x14                                // Gpio select function 5

#define GPIO_PIN_OUTPUT_SET0_OFFVALUE 0x1C       //GPIO PIN output set 0
#define GPIO_PIN_OUTPUT_SET1_OFFVALUE 0x20               //GPOIO PIN output set 1

#define GPIO_PIN_OUTPUT_CLR0_OFFVALUE 0x28       //GPIO PIN output clear 0
#define GPIO_PIN_OUTPUT_CLR1_OFFVALUE 0x2C       //GPIO pin output clear 1

#define GPIO_PIN_LEVEL0_OFFVALUE 0x34                    //Gpio Pin level 0
#define GPIO_PIN_LEVEL1_OFFVALUE 0x38                    //GPIO pin level 1 


int8_t write_buf[1024];
int8_t read_buf[1024];

#define WR_VALUE _IOW('a', 'a', int32_t *)
#define RD_VALUE _IOR('a', 'b', int32_t *)
// #define SET _IOW('a', 'c', char *)
// #define GET _IOR('a', 'd', char *)

void rsapberrypi_pinout(void);
//void GPIO_Pin_select(int gpio_pin);
void GPIO_pin_select_direction(int gpio_pin, int direction);
void GPIO_pin_set(int gpio_pin);
void GPIO_pin_clear(int gpio_pin); 

int fd;
int main()
{
       // int fd;
        int option;
        int wr_num;
        int rd_num;
        static char wr_ch;
        char rd_ch;
        void * ptr = NULL;

        uint32_t gpio_pinnum;
        int gpio_inout;

        printf("*********************************\n");
   
        fd = open("/dev/my_device", O_RDWR);
        if(fd < 0) {
                printf("Cannot open device file...\n");
                return 0;
        }

        while(1) {
                printf("\n****Please Enter the Option******\n");
                printf("        1. Write               \n");
                printf("        2. Read                 \n");
                printf("        3. write Integer        \n");
                printf("        4. Read Integer        \n");
                printf("        5. Raspberry Pi pinout Details\n");

                printf("        6. Select Pin and Direction\n");
                printf("        7. Set GPIO Pin         \n");
                printf("        8. Clear GPIO pin Select\n");
                printf("        9. Exit                 \n\n");

                printf("*********************************\n");
                scanf("%d", &option);
                printf("Your Option = %d\n", option);
                
                switch(option) {
                        case 1:
                                printf("Enter the string to write into driver :");
                                scanf("  %[^\t\n]s", write_buf);
                                printf("Data Writing ...");
                                write(fd, write_buf, strlen(write_buf)+1);
                                printf("Done!\n");
                                break;
                        case 2:
                                printf("Data Reading ...");
                                read(fd, read_buf, 1024);
                                printf("Done!\n\n");
                                printf("Data = %s\n\n", read_buf);
                                break;
                        
                        case 3:
                                printf("Enter the Number : ");
                                scanf("%d", &wr_num);
                              //  sprintf(write_buf,"%d", num);
                              //  write(fd,write_buf, 10);

                                ioctl(fd, WR_VALUE, (int32_t *)&wr_num);
                                wr_num = 0;
                                break;
                        case 4:
                                printf("Read the Number : ");
                              //  read(fd, read_buf, 10);
                              //  sscanf(read_buf,"%d",&num);
                              //  printf("\n%s\n",read_buf);

                                ioctl(fd, RD_VALUE, (int32_t *)&rd_num);
                                printf("num = %d \n", rd_num);
                        
                                break;       
                        case 5:
                                printf("\nRaspberry Pi model 3B, this will output something like the following:\n");
                                rsapberrypi_pinout();
                                break;

                        case 6:
                                printf("Enter a GPIO PIN Number[2-27] : ");
                                scanf("%u", &gpio_pinnum);

                                printf("Enter a GPIO PIN Direction[1 : Input  0 : Output] : ");
                                scanf("%d", &gpio_inout);

                                GPIO_pin_select_direction(gpio_pinnum, gpio_inout);
                                break;
                        case 7:
                                printf("Enter a GPIO PIN [output set] Number[2-27] : ");
                                scanf("%u", &gpio_pinnum);

                                GPIO_pin_set(gpio_pinnum);
                                break;        

                        case 8:
                                printf("\nEnter a GPIO PIN [output Clear] Number[2-27] : ");
                                scanf("%u", &gpio_pinnum);

                                GPIO_pin_clear(gpio_pinnum);
                                break;
                        case 9:
                                //Close the device file
                                close(fd);
                                //Close the Main Application
                                exit(1);
                                break;         
                       

                        default:
                                printf("Enter Valid option = %c\n",option);
                                break;          
                }
        }
        close(fd);
}

void GPIO_pin_select_direction(int gpio_pin, int direction)
{
        char buffer[15] = {'\0'};
        uint32_t add;
        uint32_t data;

        //here check the Gpio pin number is valid or not
        if((gpio_pin >= 2  && gpio_pin <= 27) != 1)
        {
                printf(" Enter a valid GPIO Pin Number...!!\n");
                return;
        }

        if(direction == 0)
        {
                // here check the entered gpio pin value is between 2 to 10
                // because select the gpio register -GPIOFSEL0 
                if(gpio_pin >= 2 && gpio_pin <= 9)
                {
                        add = (GPIO_FSELE0_OFFVALUE);

                        data =  (1 << ((gpio_pin%10) *3));  //or (1 << ((pin%10) *3)));

                        sprintf(buffer,"%s %u %u", "DIRO", add, data);

                }
                else if(gpio_pin >= 10 && gpio_pin <= 19)
                {
                         add = (GPIO_FSELE1_OFFVALUE);

                        data =  (1 << ((gpio_pin%10) *3));  //or (1 << ((pin%10) *3)));

                        sprintf(buffer,"%s %u %u", "DIRO", add, data);

                }
                else if(gpio_pin >= 20 && gpio_pin <= 27)
                {
                         add = (GPIO_FSELE2_OFFVALUE);

                        data =  (1 << ((gpio_pin%10) *3));  //or (1 << ((pin%10) *3)));

                        sprintf(buffer,"%s %u %u", "DIRO", add, data);

                }
        }
        else if(direction == 1)
        {
                // here check the entered gpio pin value is between 2 to 10
                // because select the gpio register -GPIOFSEL0 
                if(gpio_pin >= 2 && gpio_pin <= 9)
                {
                        add = (GPIO_FSELE0_OFFVALUE);

                        data =  ~(~(~0 << 3) << ((gpio_pin%10) *3));  //or ~(7 << ((pin%10) *3)));

                        sprintf(buffer,"%s %u %u", "DIRI", add, data);

                }
                else if(gpio_pin >= 10 && gpio_pin <= 19)
                {
                         add = (GPIO_FSELE1_OFFVALUE);

                        data =  ~(~(~0 << 3) << ((gpio_pin%10) *3));  //or ~(7 << ((pin%10) *3)));

                        sprintf(buffer,"%s %u %u", "DIRI", add, data);

                }
                else if(gpio_pin >= 20 && gpio_pin <= 27)
                {
                         add = (GPIO_FSELE2_OFFVALUE);

                        data =  ~(~(~0 << 3) << ((gpio_pin%10) *3));  //or ~(7 << ((pin%10) *3)));

                        sprintf(buffer,"%s %u %u", "DIRI", add, data);

                }

        }

        printf("GPIO Select and Direction: %s\n", buffer);

        write(fd, buffer, strlen(buffer)+1);

}

void GPIO_pin_set(int gpio_pin)
{
        char buffer[15] = {'\0'};
        uint32_t add;
        uint32_t data;
        //here check the Gpio pin number is valid or not
        if((gpio_pin >= 2  && gpio_pin <= 27) != 1)
        {
                printf(" Enter a valid GPIO Pin Number...!!\n");
                return;
        }

        add = (GPIO_PIN_OUTPUT_SET0_OFFVALUE);

        data =  (1 << gpio_pin);  

        sprintf(buffer,"%s %u %u", "SET", add, data);

         printf("GPIO Set : %s\n", buffer);

         write(fd, buffer, strlen(buffer)+1);

}
void GPIO_pin_clear(int gpio_pin)
{
        char buffer[15] = {'\0'};
        uint32_t add;
        uint32_t data;
        //here check the Gpio pin number is valid or not
        if((gpio_pin >= 2  && gpio_pin <= 27) != 1)
        {
                printf(" Enter a valid GPIO Pin Number...!!\n");
                return;
        }

        add = (GPIO_PIN_OUTPUT_CLR0_OFFVALUE);

        data =  (1 << gpio_pin);  

        sprintf(buffer,"%s %u %u", "SET", add, data);

         printf("GPIO Set : %s\n", buffer);

         write(fd, buffer, strlen(buffer)+1);
}

void rsapberrypi_pinout(void)
{
        printf(",--------------------------------.  \n");
        printf("| oooooooooooooooooooo J8     +==== | \n");
        printf("| 1ooooooooooooooooooo        | USB \n");
        printf("|                             +==== \n");
        printf("|      Pi Model 3B V1.2          | \n");
        printf("|      +----+                 +==== \n");
        printf("| |D|  |SoC |                 | USB \n");
        printf("| |S|  |    |                 +==== \n");
        printf("| |I|  +----+                    | \n");
        printf("|                   |C|     +====== \n");
        printf("|                   |S|     |   Net \n");
        printf("| pwr        |HDMI| |I||A|  +====== \n");
        printf("`-| |--------|    |----|V|------- \n");


        printf("Revision           : a02082 \n");
        printf("SoC                : BCM2837 \n");
        printf("RAM                : 1024Mb \n");
        printf("Storage            : MicroSD \n");
        printf("USB ports          : 4 (excluding power) \n");
        printf("Ethernet ports     : 1 \n");
        printf("Wi-fi              : True \n");
        printf("Bluetooth          : True \n");
        printf("Camera ports (CSI) : 1 \n");
        printf("Display ports (DSI): 1 \n");

        printf("J8: \n");
        printf("   3V3  (1) (2)  5V \n");
        printf(" GPIO2  (3) (4)  5V \n");
        printf(" GPIO3  (5) (6)  GND \n");
        printf(" GPIO4  (7) (8)  GPIO14 \n");
        printf("   GND  (9) (10) GPIO15 \n");
        printf("GPIO17 (11) (12) GPIO18 \n");
        printf("GPIO27 (13) (14) GND \n");
        printf("GPIO22 (15) (16) GPIO23 \n");
        printf("   3V3 (17) (18) GPIO24 \n");
        printf("GPIO10 (19) (20) GND \n");
        printf(" GPIO9 (21) (22) GPIO25 \n");
        printf("GPIO11 (23) (24) GPIO8 \n");
        printf("  GND (25) (26) GPIO7 \n");
        printf(" GPIO0 (27) (28) GPIO1 \n");
        printf(" GPIO5 (29) (30) GND \n");
        printf(" GPIO6 (31) (32) GPIO12 \n");
        printf("GPIO13 (33) (34) GND \n");
        printf("GPIO19 (35) (36) GPIO16 \n");
        printf("GPIO26 (37) (38) GPIO20 \n");
        printf("   GND (39) (40) GPIO21 \n");
}
