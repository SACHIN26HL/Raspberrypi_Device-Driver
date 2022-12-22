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
#include <linux/interrupt.h>
#include <asm/io.h>
#include <linux/err.h>
#include <linux/kobject.h>
#include <linux/sysfs.h>
#define memory_size 1024    //memory size


//ioctl commands - Macro 
#define WR_VALUE _IOW('a', 'a', int32_t *)
#define RD_VALUE _IOR('a', 'b', int32_t *)
#define SET _IOW('a', 'c', char *)
#define GET _IOR('a', 'd', char *)

#define IRQ_NO 1  
unsigned long int i=0;

/*tasklet function prototype*/
void tasklet_fun(unsigned long int);

struct tasklet_struct *tasklet ;//=  NULL, 0, 0, tasklet_function, 1 };

/*declare the tasklet static method */
DECLARE_TASKLET(tasklet, tasklet_fun, 1);




/*tasklet function body*/
void tasklet_fun(unsigned long int data)
{

	printk(KERN_INFO "Executing the tasklet function : data = %ld\n", data);
}

static irqreturn_t irq_handler(int irq, void *dev_id)
{
	printk(KERN_INFO "interrupt Occurred data: %ld\n", i);
	i++;
	tasklet_schedule(&tasklet);
	return IRQ_HANDLED;

}

int32_t my_value =0;
char my_char ;


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


static struct file_operations fops =
{
	.owner = THIS_MODULE,
	.read  = my_device_fileread,
	.write = my_device_filewrite,
	.open  = my_device_fileopen,
	.unlocked_ioctl = my_ioctl,
	.release = my_device_filerelease,
};


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
	
	
	//pr_info("kernel buf=%s",buf);
	pr_info("Write to kernel buf=%s\n",kernel_buffer);

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

	strcpy(kernel_buffer,"Memory Allocated");
	
	if (request_irq(IRQ_NO, irq_handler, IRQF_SHARED, "my_etx_device", (void *)(irq_handler))) {
            printk(KERN_INFO "my_device: cannot register IRQ ");
                    goto irq;
        }
	

      /* tasklet = kmalloc(sizeof(struct tasklet_struct), GFP_KERNEL);
	if(tasklet == NULL)
	{
		pr_info("can't allocate the memory");
		goto irq;
	}	
	*/
	/*tasklet dynamic initialization*/
//tasklet_init(tasklet, tasklet_fun, 1);
        printk(KERN_INFO "Device Driver Insert...Done!!!\n");
 
	
	printk(KERN_INFO " Welcome \n");
	printk(KERN_INFO " This is simple Module Driver \n");
	printk(KERN_INFO " kernel Module Inserted Successfully \n");

	return 0;

irq:
        free_irq(IRQ_NO,(void *)(irq_handler));

r_device:
	class_destroy(dev_class);

r_class:
	unregister_chrdev_region(dev,1);

  	return -1;

}


//Module Exit function
static void __exit my_driver_exit(void)
{
       	tasklet_kill(&tasklet);
        free_irq(IRQ_NO,(void *)(irq_handler));
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

