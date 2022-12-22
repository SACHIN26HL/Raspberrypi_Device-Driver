#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>


int m_value = 0;
char m_char_value = '0';
int m_array[3];

module_param(m_value, int, S_IRUSR|S_IWUSR);

//module_param(m_char_value, char, S_IRUSR|S_IWUSR);

module_param_array(m_array, int,NULL, S_IRUSR|S_IWUSR);


//module Init function

static int __init my_driver_init(void)
{
	int i;
	printk(KERN_INFO " Welcome \n");
	printk(KERN_INFO " This is simple Module Driver \n");
	printk(KERN_INFO " kernel Module Inserted Successfully \n");


	printk(KERN_INFO "m_value = %d \n", m_value);
	printk(KERN_INFO "m_char_value = %c \n", m_char_value);

	for( i =0; i < 3; i++)
	{

		printk(KERN_INFO "m_array[%d] = %d \n", i, m_array[i]);
	}
	
	return 0;

}



//module Exit function


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
	
