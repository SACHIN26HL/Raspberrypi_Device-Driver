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

#define GPIO_BASE_ADD 0x3F200000

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
void GPIO_Pin_select(int gpio_pin);
void GPIO_pin_select_direction(int gpio_pin, int direction);
void GPIO_pin_set(int gpio_pin);
void GPIO_pin_clear(int gpio_pin); 

int8_t send_buf[120];
int main()
{

	int fd;
	int option =0;
	int wr_num;
	int rd_num;
	static char wr_ch;
	char rd_ch;
	void * ptr = NULL;

	int gpio_pinnum = 21;
	int gpio_inout =0;

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

		printf("	6. Select pin		\n");
		printf("        7. Select Pin and Direction\n");
		printf("        8. Set GPIO Pin         \n");
		printf("        9. Clear GPIO pin Select\n");
		printf("        10. Exit                 \n\n");

		printf("*********************************\n");

		scanf("%d", &option);
		fflush(stdout);
		fflush(stdin);
		printf("Your Option = %d", option);

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
				printf("Enter a GPIO Pin Number[2-27] :\n");
				scanf("%d", &gpio_pinnum);

				GPIO_Pin_select(gpio_pinnum);

				write(fd, write_buf, strlen(write_buf)+1);
				break;

			case 7:
				printf("Enter a GPIO PIN Number[2-27] :\n");
				scanf("%d", &gpio_pinnum);

				printf("Enter a GPIO PIN Direction[1 : Input  0 : Output] :\n");
				scanf("%d", &gpio_inout);

				GPIO_pin_select_direction(gpio_pinnum, gpio_inout);

				printf("....send info......");

				printf("\nwrite buf : %s\n", write_buf);

				write(fd, write_buf, strlen(write_buf)+1);
				//		write(fd, send_buf, strlen(send_buf)+1);
				//		write(fd, "send_buf", 10);
				break;
			case 8:
				printf("Enter a GPIO PIN [output set] Number[2-27] :\n");
				scanf("%d", &gpio_pinnum);

				GPIO_pin_set(gpio_pinnum);
				write(fd, write_buf, strlen(write_buf)+1);
				break;        

			case 9:
				printf("\nEnter a GPIO PIN [output Clear] Number[2-27] : ");
				scanf("%d", &gpio_pinnum);

				GPIO_pin_clear(gpio_pinnum);
				write(fd, write_buf, strlen(write_buf)+1);
				break;
			case 10:
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
void GPIO_Pin_select(int gpio_pin)
{
	char buffer[100] = {'\0'};
	uint32_t add;
	uint32_t data;

	//here check the Gpio pin number is valid or not
	if((gpio_pin >= 2  && gpio_pin <= 27) != 1)
	{
		printf(" Enter a valid GPIO Pin Number...!!\n");
		return;
	}
	if(gpio_pin >= 2 && gpio_pin <= 9)
	{
		add = (GPIO_FSELE0_OFFVALUE);

		data =  ~(~(~0 << 3) << ((gpio_pin%10) *3));  //or ~(7 << ((pin%10) *3)));

		sprintf(buffer,"%s %u %d ", "PIN", add, data);

	}
	else if(gpio_pin >= 10 && gpio_pin <= 19)
	{
		add = (GPIO_FSELE1_OFFVALUE);

		data =  ~(~(~0 << 3) << ((gpio_pin%10) *3));  //or ~(7 << ((pin%10) *3)));
		sprintf(buffer,"%s %u %u ", "PIN", add, data);

	}
	else if(gpio_pin >= 20 && gpio_pin <= 27)
	{
		add = (GPIO_FSELE2_OFFVALUE);

		data =  ~(~(~0 << 3) << ((gpio_pin%10) *3));  //or ~(7 << ((pin%10) *3)));
		sprintf(buffer,"%s %u %u ", "PIN", add, data);

	}

	strcpy(write_buf,buffer);
	printf("\nGPIO Selected Pin is  : %s\n", write_buf);

}
void GPIO_pin_select_direction(int gpio_pin, int direction)
{
	char buffer[100] = {'\0'};
	uint32_t add;
	uint32_t data;

	//here check the Gpio pin number is valid or not
	if((gpio_pin >= 2  && gpio_pin <= 27) != 1)
	{
		printf(" Enter a valid GPIO Pin Number...!!\n");
		return;
	}

	printf("............111111111111111111111111111111111...");
	if(direction == 0)
	{
		// here check the entered gpio pin value is between 2 to 10
		// because select the gpio register -GPIOFSEL0 
		if(gpio_pin >= 2 && gpio_pin <= 9)
		{
			add = (GPIO_FSELE0_OFFVALUE);

			data =  (1 << ((gpio_pin%10) *3));  //or (1 << ((pin%10) *3)));


			sprintf(buffer,"%s %u %d ", buffer, add, data);

		}
		else if(gpio_pin >= 10 && gpio_pin <= 19)
		{
			add = (GPIO_FSELE1_OFFVALUE);

			data =  (1 << ((gpio_pin%10) *3));  //or (1 << ((pin%10) *3)));

			sprintf(buffer,"%s %u %u ", "DIRO", add, data);

		}
		else if(gpio_pin >= 20 && gpio_pin <= 27)
		{
			add = (GPIO_FSELE2_OFFVALUE);

			data =  (1 << ((gpio_pin%10) *3));  //or (1 << ((pin%10) *3)));

			sprintf(buffer,"%s %u %u ", "DIRO", add, data);

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

			sprintf(buffer,"%s %u %u ", "DIRI", add, data);

		}
		else if(gpio_pin >= 10 && gpio_pin <= 19)
		{
			add = (GPIO_FSELE1_OFFVALUE);

			data =  ~(~(~0 << 3) << ((gpio_pin%10) *3));  //or ~(7 << ((pin%10) *3)));

			sprintf(buffer,"%s %u %u ", "DIRI", add, data);

		}
		else if(gpio_pin >= 20 && gpio_pin <= 27)
		{
			add = (GPIO_FSELE2_OFFVALUE);

			data =  ~(~(~0 << 3) << ((gpio_pin%10) *3));  //or ~(7 << ((pin%10) *3)));

			sprintf(buffer,"%s %u %u ", "DIRI", add, data);

		}

	}

	//	printf("........22.......");
	//	printf("GPIO Select and Direction: %s\n", buffer);

	strcpy(write_buf,buffer);
	//	write(fd, buffer, sizeof(buffer)+1);
	printf("...........33....");
	printf("\nGPIO Select and Direction: %s\n", write_buf);
	printf("#############");
	return;
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

	strcpy(write_buf,buffer);
	//	write(fd, buffer, strlen(buffer)+1);

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

	printf("GPIO CLR : %s\n", buffer);

	strcpy(write_buf,buffer);
	//	write(fd, buffer, strlen(buffer)+1);
}

void rsapberrypi_pinout(void)
{
	system("pinout");
}
