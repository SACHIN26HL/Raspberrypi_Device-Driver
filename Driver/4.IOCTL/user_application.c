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

int8_t write_buf[1024];
int8_t read_buf[1024];

#define WR_VALUE _IOW('a', 'a', int32_t *)
#define RD_VALUE _IOR('a', 'b', int32_t *)
// #define SET _IOW('a', 'c', char *)
// #define GET _IOR('a', 'd', char *)

int main()
{
        int fd;
        int option;
        int wr_num;
        int rd_num;
        static char wr_ch;
        char rd_ch;
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
                printf("        3. write Integer        \n");
                printf("        4. Read Integer        \n");
                printf("        6. write char       \n");
                printf("        7. Read char        \n");
                printf("        5. Exit                 \n\n");
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
                                close(fd);
                                exit(1);
                                break;         
                       

                 /*       case 6:

                                
                             //   printf("dd:");
                             //   scanf("%d", &wr_num);

                                printf("Enter the character:\t");
                                scanf("%c", &wr_ch);
                                scanf("%c", &wr_ch);
                             //   scanf("%c", &wr_ch);
                              
                              printf("\n Enter ch is : %c", wr_ch);
                                ioctl(fd, SET, (char *)&wr_ch);
                               // wr_ch++;
                                break;
                        case 7:
                                printf("Read the Number : ");
                              

                                ioctl(fd, GET, (char *)&rd_ch);
                                printf("ch = %c \n", rd_ch);
                        
                 */               break;   

                        default:
                                printf("Enter Valid option = %c\n",option);
                                break;          
                }
        }
        close(fd);
}
