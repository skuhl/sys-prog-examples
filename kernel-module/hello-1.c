//http://www.thegeekstuff.com/2013/07/write-linux-kernel-module/
// lsmod - lists installed kernel modules
// modinfo - print information about a kernel module
// insprobe - install a kernel module (simple)
// modprobe - install a kernel module (more clever)
// rmmod - remove a kernel module.
//
// You may need to be root to compile this on your computer (depending
// on your machine). You MUST be root to be able to insert the module.
//
// Recommended commands:
// make
// modinfo ./hello.ko
// insmod ./hello.ko
// lsmod | grep hello
// dmesg


/*  
 *  hello-1.c - The simplest kernel module.
 */
#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */

int init_module(void)
{
	printk(KERN_INFO "Hello world 1.\n");

	/* 
	 * A non 0 return means init_module failed; module can't be loaded. 
	 */
	return 0;
}

void cleanup_module(void)
{
	printk(KERN_INFO "Goodbye world 1.\n");
}
