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

int8_t write_buf[1024];
int8_t read_buf[1024];

int main()
{
        int fd;
        char option;
        int num;
        void * ptr = NULL;
        printf("*********************************\n");
   
        fd = open("/dev/my_device", O_RDWR);
        if(fd < 0) {
                printf("Cannot open device file...\n");
                return 0;
        }

        while(1) {
                printf("****Please Enter the Option******\n");
                printf("        1. Write               \n");
                printf("        2. Read                 \n");
                printf("        3. Exit                 \n\n");
                printf("        4. write Integer        \n");
                printf("        5. Read Integer        \n");
                printf("*********************************\n");
                scanf(" %c", &option);
                printf("Your Option = %c\n", option);
                
                switch(option) {
                        case '1':
                                printf("Enter the string to write into driver :");
                                scanf("  %[^\t\n]s", write_buf);
                                printf("Data Writing ...");
                                write(fd, write_buf, strlen(write_buf)+1);
                                printf("Done!\n");
                                break;
                        case '2':
                                printf("Data Reading ...");
                                read(fd, read_buf, 1024);
                                printf("Done!\n\n");
                                printf("Data = %s\n\n", read_buf);
                                break;
                        case '3':
                                close(fd);
                                exit(1);
                                break;

                        case '4':
                                printf("Enter the Number : ");
                                scanf("%d", &num);
                                sprintf(write_buf,"%d", num);
                                write(fd,write_buf, 10);
                                num = 0;
                                break;
                        case '5':
                                printf("Read the Number : ");
                                read(fd, read_buf, 10);
                                
                                sscanf(read_buf,"%d",&num);
                                printf("\n%s\n",read_buf);
                                printf("num = %d \n", num);
                                num = 0;
                                break;        
                        default:
                                printf("Enter Valid option = %c\n",option);
                                break;
                }
        }
        close(fd);
}
