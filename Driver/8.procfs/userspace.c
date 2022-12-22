#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{

	int fd;
	int option;
	char read_arr[100];
	char array[100];

	fd = open("/dev/etx_device", O_RDWR);

	if(fd < -1)
	{
		printf("File open error ...!");
		return 0;
	}

	while(1)
	{
		printf("1. Read\n 2. Write \n 3. exit\n");
		printf("Select option: ");
		scanf("%d", &option);
		switch(option)
		{
			case 1:
				read(fd, read_arr, 100);
				printf("read info: %s\n", read_arr);
				
				break;

			case 2:
				printf("Enter a string: ");
				scanf("%s", array);

				write(fd, array, 100);

				break;

			case 3:
				printf("End...!");
				close(fd);
				return 0;
				
		}

	}
	return 0;
}
