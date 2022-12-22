#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/kdev_t.h>


//creating a dev with our own major and minor number

//dev_t dev = MKDEV(502, 0);   //statically major number allocation


dev_t dev = 0;    //dynamically major number allocation
static struct class * dev_class;



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

	if((dev_class = class_create(THIS_MODULE, "my_device_class")) == NULL)
	{
		pr_err("can't create the  struct class for devices\n");
		goto r_class;
	}

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
	unregister_chrdev_region(dev,1);
	printk(KERN_INFO "kernel module Removed successfully....!\n");
}

module_init(my_driver_init);
module_exit(my_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sachin");
MODULE_DESCRIPTION("Simple module-- driver (automatically creating a devices file)");
MODULE_VERSION("1:0.0");
	
