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
	{ 0xcb440b5e, "module_layout" },
	{ 0x37fd21cc, "device_destroy" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x8eab5523, "class_destroy" },
	{ 0x85401a17, "device_create" },
	{ 0x109c449a, "__class_create" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0x92997ed8, "_printk" },
	{ 0xbdfb6dbb, "__fentry__" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "55B9471806EC2FAB8533241");
