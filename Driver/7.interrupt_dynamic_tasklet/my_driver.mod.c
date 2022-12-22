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
	{ 0xc4162456, "module_layout" },
	{ 0xeb50e36b, "cdev_del" },
	{ 0xa9162ccf, "device_destroy" },
	{ 0x37a0cba, "kfree" },
	{ 0xea3c74e, "tasklet_kill" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0xdb8c13c, "class_destroy" },
	{ 0xc1514a3b, "free_irq" },
	{ 0x2364c85a, "tasklet_init" },
	{ 0x92d5838e, "request_threaded_irq" },
	{ 0xa926a2db, "kmem_cache_alloc_trace" },
	{ 0x57b41c5c, "kmalloc_caches" },
	{ 0xe4ca90e9, "device_create" },
	{ 0xe72972aa, "__class_create" },
	{ 0xf99f641, "cdev_add" },
	{ 0x1bd8b5c, "cdev_init" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0x13c49cc2, "_copy_from_user" },
	{ 0x6b10bee1, "_copy_to_user" },
	{ 0x88db9f48, "__check_object_size" },
	{ 0x9d2ab8ac, "__tasklet_schedule" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0x92997ed8, "_printk" },
	{ 0xbdfb6dbb, "__fentry__" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "AAB5726470CC665FE0E111D");
