#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>


//module Init function

static int __init my_driver_init(void)
{
	printk(KERN_INFO " Welcome \n");
	printk(KERN_INFO " This is simple Module Driver \n");
	printk(KERN_INFO " kernel Module Inserted Successfully \n");

  	return 0;

}


//Module Exit function


static void __exit my_driver_exit(void)
{
	printk(KERN_INFO "kernel module Removed successfully....!\n");
}

module_init(my_driver_init);
module_exit(my_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sachin");
MODULE_DESCRIPTION("Simple module-- driver");
MODULE_VERSION("1:0.0");
	
