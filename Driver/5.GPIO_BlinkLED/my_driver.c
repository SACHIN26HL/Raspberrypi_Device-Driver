#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/kdev_t.h>
#include <linux/cdev.h>
#include <linux/slab.h>  //kmalloc()
#include <linux/uaccess.h>   //copy_to/from_user()
#include <linux/ioctl.h>
#include <asm/io.h>

#include "bcm2837.h"   //User defined header file

#define memory_size 1024    //memory size

//ioctl commands - Macro 
#define WR_VALUE _IOW('a', 'a', int32_t *)
#define RD_VALUE _IOR('a', 'b', int32_t *)


uint32_t *sel_reg; // Virtual address
uint32_t *tmp_sel_reg; // temporary virtual address

int32_t my_value =0;
char my_char ;

// This variable used for save the userapplication inputs
char cmd[5]={'\0'};   
uint32_t pin_address;
uint32_t set_data;
uint32_t get_data;


//creating a dev with our own major and minor number
//dev_t dev = MKDEV(502, 0);   //statically major number allocation


dev_t dev = 0;    //dynamically major number allocation
static struct class * dev_class; // class for devices file creation  automatically
static struct cdev my_cdev; 	 // cdev structure for file operation
char *kernel_buffer;

//Function Prototypes

static int my_device_fileopen(struct inode *inode, struct file *file);
static int my_device_filerelease(struct inode *inode, struct file * file);
static ssize_t my_device_fileread(struct file *filep, char  *buf, size_t len, loff_t * off);
static ssize_t my_device_filewrite(struct file *flip, const char *buf, size_t len, loff_t * off);

static long my_ioctl(struct file *file, unsigned int command, unsigned long argument);



//File operation Structure 
static struct file_operations fops =
{
	.owner = THIS_MODULE,
	.read  = my_device_fileread,
	.write = my_device_filewrite,
	.open  = my_device_fileopen,
	.unlocked_ioctl = my_ioctl,
	.release = my_device_filerelease,
};


//IOCTL function definition
static long my_ioctl(struct file *file, unsigned int command, unsigned long argument)
{

	pr_info("commands value RD_VALUE = %ld command = %d\n", RD_VALUE, command);
	switch(command)
	{
		case RD_VALUE:

			if(copy_to_user((int32_t *)argument, &my_value, sizeof(my_value)))
			{
				printk(KERN_INFO "DATA Read ... error\n");
			}

			break;

		case WR_VALUE :

			if(copy_from_user(&my_value, (int32_t *)argument, sizeof(my_value)))
			{
				printk(KERN_INFO "DATA Write ... error\n");

			}

			printk(KERN_INFO " Value id : %d \n", my_value);
			break;

		default:
		    printk(KERN_INFO ".......Wrong command...........!!!\n");
		    break;
	}
	return 0;
}


//this function will be called when we open the device file
static int my_device_fileopen(struct inode *inod, struct file * file)
{
	pr_info("Driver open function called ............!!!!...\n");
	return 0;
}

//this function will be called when we close the device file
static int my_device_filerelease(struct inode *inode, struct file *file)
{
	pr_info("Driver release/close function called.......!!!..\n");
	return 0;
}

//this function will be called when we read the device file
static ssize_t my_device_fileread(struct file *filp, char *buf, size_t len, loff_t *off)
{
	
	printk(KERN_INFO "Read from kernel_buffer = %s\n", kernel_buffer);

//	int num1;
//	sscanf(kernel_buffer, "%d", &num1);
//	printk(KERN_INFO "\nnum1 = %d\n", num1);

	if(copy_to_user(buf,kernel_buffer, len))
	{
		pr_err("data read : error.....!!...\n");
	}

	
	printk(KERN_INFO "Driver Read function called ....!!!...\n");
	return memory_size;
}

//this function will be called when we write the device file
static ssize_t my_device_filewrite(struct file *filp, const char *buf, size_t len, loff_t *off)
{
	//pr_info("user buf=%s\n",buf);
	if(copy_from_user(kernel_buffer,buf,len))
	{
		
		pr_err("Data write: error....!!....\n");
	}
	
	sscanf(kernel_buffer,"%s %u %u", cmd, pin_address, set_data);
	//pr_info("kernel buf=%s",buf);
	pr_info("Write to kernel buf=%s\n",kernel_buffer);

     
	/*Comaprision for select pin, direction, set and clear pin */
    if(strcmp(cmd, "PIN") == 0)
    {

    	tmp_sel_reg = (uint32_t )(*sel_reg + pin_address);

    	*tmp_sel_reg |= set_data;

    }
    else if(strcmp(cmd, "DIRI") == 0)
    {
    	tmp_sel_reg = (uint32_t )(*sel_reg + pin_address);

    	*tmp_sel_reg &= set_data;

    }
    else if(strcmp(cmd, "DIRO") == 0)
    {
    	tmp_sel_reg = *sel_reg + pin_address;

    	*tmp_sel_reg |= set_data;

    }
    else if(strcmp(cmd, "SET") == 0)
    {
    	tmp_sel_reg = *sel_reg + pin_address;

    	*tmp_sel_reg |= set_data;

    }
    else if(strcmp(cmd, "CLR") == 0)
    {
    	tmp_sel_reg = *sel_reg + pin_address;

    	*tmp_sel_reg |= set_data;

    }
    else
    {
    	printk(KERN_INFO "PIN or Address or data or command is Invalid...!...!!!..\n");

    }

    pr_info("GPIO add and data : %p %u \n", tmp_sel_reg, *tmp_sel_reg);

	printk(KERN_INFO "Driver write function called....!...!!!..\n");
	return len;
}

//module Init function
static int __init my_driver_init(void)
{

	pr_info("...............start my driver ...................");

	//register_chrdev_region(dev,1, "my_device_drive");  //statically major number create function
	if((alloc_chrdev_region(&dev, 0, 1, "my_device_driver_dy")) < 0)
	{
		printk(KERN_INFO "cannot allocating major number for devices 1\n");
		return -1;
	}

	//Print MINOR and Major number
	pr_info("major =%d Minor =%d \n", MAJOR(dev), MINOR(dev));


	//creating a cdev structure
	cdev_init(&my_cdev, &fops);

	//adding a character device to  the system
	if((cdev_add(&my_cdev, dev, 1)) < 0)
	{
		pr_err("Can't add the device to the system..\n");
		goto r_class;
	}

	//creating a class
	if((dev_class = class_create(THIS_MODULE, "my_device_class")) == NULL)
	{
		pr_err("can't create the  struct class for devices\n");
		goto r_class;
	}

	//creating a device
	if((device_create(dev_class, NULL, dev, NULL,"my_device")) ==NULL)
	{
		pr_err("can't create the device\n");
		goto r_device;
	}

	//creating the physical memory
	if((kernel_buffer =kmalloc(memory_size, GFP_KERNEL)) == 0)
	{
		pr_err(" can't allocate memory in kernel ....!!!...\n");
		goto r_device;
	}

	//Default message in kernel  buffer
	strcpy(kernel_buffer,"Memory Allocated");


	
	//IOremap to GPIO base address
/*	if ((sel_reg = (uint32_t *)ioremap(GPIO_BASE_ADD,0X04))==NULL)
	{
		printk(KERN_INFO "IOREMAP FAIL");
		return -1;
	}
*/	printk(KERN_INFO "IOREMAP Successfully done value is : %p", sel_reg);



	printk(KERN_INFO " Welcome \n");
	printk(KERN_INFO " This is simple Module Driver \n");
	printk(KERN_INFO " kernel Module Inserted Successfully \n");

	return 0;

r_device:
	class_destroy(dev_class);

r_class:
	unregister_chrdev_region(dev,1);

  	return -1;

}


//Module Exit function
static void __exit my_driver_exit(void)
{
	
	kfree(kernel_buffer);   //free kernelallocating memory
	device_destroy(dev_class, dev);
	class_destroy(dev_class);
	cdev_del(&my_cdev);
	unregister_chrdev_region(dev,1);
	printk(KERN_INFO "kernel module Removed successfully....!\n");
}



module_init(my_driver_init);
module_exit(my_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sachin");
MODULE_DESCRIPTION("Simple module-- driver IOCTL");
MODULE_VERSION("1:0.0");

