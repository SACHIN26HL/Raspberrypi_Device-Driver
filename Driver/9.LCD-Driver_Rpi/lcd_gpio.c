/**************************
 *
 *Simple lcd interface application
 *file : lcd_gpio.c
 *Date : 18/12/2022
 ***************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int main()
{
	int option;
	char ch;
	char str[100];
	int fd;

	fd = open("/dev/etx_mydevice", O_RDWR);

	if(fd < 0){
		printf("error in open file\n");
		return 0;
	}
	//lcd_and_gpio_pin_init();
	//lcd_init();

	while(1)
	{
		printf("\nSelect options\n1. write char \n2.write string\n3.exit\nEnter Here :");
		scanf("%d", &option);

		switch(option)
		{
			case 1:
				printf("\nEnter a character : ");
				scanf("%c", &ch);
				write(fd,&ch, 1);
				break;
			case 2:
				printf("\nEnter a string : ");
				scanf("%s", str);
				write(fd,str, strlen(str)+1);
				break;
			case 3:
				exit(1);
				break;
			default:
				printf("\nSelect a valid option\n\n");
		}
	}

	return 0;
}
