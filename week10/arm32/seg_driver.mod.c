#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
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
	{ 0xb1ad28e0, "__gnu_mcount_nc" },
	{ 0x92997ed8, "_printk" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0x8f678b07, "__stack_chk_guard" },
	{ 0x77a6b26, "gpio_to_desc" },
	{ 0xc867a600, "gpiod_set_raw_value" },
	{ 0xae353d77, "arm_copy_from_user" },
	{ 0x5f754e5a, "memset" },
	{ 0x3ea1b6e4, "__stack_chk_fail" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0xfcd2e0ea, "__class_create" },
	{ 0xa327c994, "device_create" },
	{ 0xd4bd59e, "cdev_init" },
	{ 0x507ff4e8, "cdev_add" },
	{ 0x47229b5c, "gpio_request" },
	{ 0xb0b98386, "gpiod_direction_output_raw" },
	{ 0xfe990052, "gpio_free" },
	{ 0x473972fd, "device_destroy" },
	{ 0xc9b921cc, "class_destroy" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x29a0b75a, "cdev_del" },
	{ 0xb899592f, "module_layout" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "C4B98EF2503B45279C042C0");
