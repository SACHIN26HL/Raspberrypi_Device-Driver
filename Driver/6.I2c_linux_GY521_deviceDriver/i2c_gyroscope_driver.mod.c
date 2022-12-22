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
	{ 0x2cb61b30, "i2c_del_driver" },
	{ 0xbb0f4c80, "i2c_unregister_device" },
	{ 0x5baf3a2c, "i2c_put_adapter" },
	{ 0x41fd162a, "i2c_register_driver" },
	{ 0x9b908846, "i2c_new_client_device" },
	{ 0x87c26126, "i2c_get_adapter" },
	{ 0x4faee08f, "i2c_smbus_write_byte_data" },
	{ 0x2ffd7757, "i2c_smbus_read_byte_data" },
	{ 0xf9a482f9, "msleep" },
	{ 0x9b6adf5b, "_dev_info" },
	{ 0x8da6585d, "__stack_chk_fail" },
	{ 0xbfd0b0d8, "i2c_transfer_buffer_flags" },
	{ 0x92997ed8, "_printk" },
};

MODULE_INFO(depends, "");

MODULE_ALIAS("i2c:ETX_MPU6050");

MODULE_INFO(srcversion, "FD8081196F5CE5A132B90AF");
