#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xd8f378f4, "module_layout" },
	{ 0x1b2cdfe8, "gpiod_unexport" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0xa9f10fe, "cdev_del" },
	{ 0xdb3169d4, "class_destroy" },
	{ 0xe9cd00ad, "device_destroy" },
	{ 0xa38c6fe3, "gpiod_export" },
	{ 0xec52b35a, "gpiod_direction_output_raw" },
	{ 0xfe990052, "gpio_free" },
	{ 0x47229b5c, "gpio_request" },
	{ 0x1c45809d, "device_create" },
	{ 0x8612a620, "__class_create" },
	{ 0xea41867b, "cdev_add" },
	{ 0x81f3ee7, "cdev_init" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0x7eb85350, "gpiod_set_raw_value" },
	{ 0x56470118, "__warn_printk" },
	{ 0xdcb764ad, "memset" },
	{ 0x12a4e128, "__arch_copy_from_user" },
	{ 0x8da6585d, "__stack_chk_fail" },
	{ 0x6cbbfc54, "__arch_copy_to_user" },
	{ 0x750047cf, "gpiod_get_raw_value" },
	{ 0x74bafb64, "gpio_to_desc" },
	{ 0x92997ed8, "_printk" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "8B2E676278D3B28498B94D3");
