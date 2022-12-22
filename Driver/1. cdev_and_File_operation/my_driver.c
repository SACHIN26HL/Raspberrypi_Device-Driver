#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/kdev_t.h>
#include <linux/cdev.h>


//creating a dev with our own major and minor number

//dev_t dev = MKDEV(502, 0);   //statically major number allocation


dev_t dev = 0;    //dynamically major number allocation

static struct class * dev_class; // class for devices file creation  automatically

static struct cdev my_cdev; // cdev structure for file operation

//Function Prototypes

static int my_device_fileopen(struct inode *inode, struct file *file);
static int my_device_filerelease(struct inode *inode, struct file * file);
static ssize_t my_device_fileread(struct file *filep, char  *buf, size_t len, loff_t * off);
static ssize_t my_device_filewrite(struct file *flip, const char *buf, size_t len, loff_t * off);


static struct file_operations fops =
{
	.owner = THIS_MODULE,
	.read  = my_device_fileread,
	.write = my_device_filewrite,
	.open  = my_device_fileopen,
	.release = my_device_filerelease,
};



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

static ssize_t my_device_fileread(struct file *filp, char  *buf, size_t len, loff_t *off)
{
	printk(KERN_INFO "Driver Read function called ....!!!...\n");
	return 0;
}

//this function will be called when we write the device file

static ssize_t my_device_filewrite(struct file *filp, const char *buf, size_t len, loff_t *off)
{
	printk(KERN_INFO "Driver write function called....!...!!!..\n");
	return 0;
}

//module Init function

static int __init my_driver_init(void)
{

	pr_info("...............start my driver ...................");

	//register_chrdev_region(dev,1, "my_device_drive");  //statically major number create function
	
	if((alloc_chrdev_region(&dev, 0,1, "my_device_driver_dy")) < 0)
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
MODULE_DESCRIPTION("Simple module-- driver (automatically creating a devices file)");
MODULE_VERSION("1:0.0");
	
