/**
 * simple.c
 *
 * A kernel program to load and unload modules to kernel
 * Operating System Concepts - 10th Edition
 * Written by Sooraj Poojary
 *
 */



#include <linux/module.h>  /*This is where module_init and module_exit are defined*/ 
#include <linux/init.h>    /*This header file includes all things related to __init part*/
#include <linux/hash.h>    /*header file for hashing functions which has a constant value GOLDEN_RATIO_PRIME*/
#include <linux/gcd.h>     /*This header file is used to access the gcd() function*/
#include <asm/uaccess.h> /*This header file use to access the HZ determine the frequency of time interrupt*/
#include <linux/jiffies.h> /*header file to access global  jiffies variable  which maintains the number of timer interrupts */
#include <asm/param.h>     /* this header file used to access HZ or frequency of time interrupt */



MODULE_LICENSE("GPL"); /*To use any other system libraries running under GPL license*/
MODULE_AUTHOR("Sooraj Poojary"); /* macro represents the author of the kernel code*/
MODULE_DESCRIPTION("PROGRAM TO  PRINT GOLDEN_RATIO_PRIME JIFFIES GCD , ALSO TO LOAD AND REMOVE KERNEL MODULES"); /*This macro contains the description of the present working kernel code*/



unsigned long int initial_time, final_time; /*To store value of jiffies during loading and unloading of module*/



/**
 * this is the function that says what work must be done once module_init(func_name) 
 * is invoked during loading of the kernel taking this function name as its parameter
 */

static int __init simple_init(void)
{
	initial_time = jiffies;/*store jiffies time during loading module*/
	printk("\nHello kernel, loading the current kernel..!\n");
	printk("Golden ratio prime: %llu\n", GOLDEN_RATIO_PRIME);
	printk("Jiffies or total interrupts from system boot: %lu\n HZ or the frequency of time interrupt: %d\n\n", jiffies, HZ);
	return 0;
}

/*
 * This is the function that says what work must be done once module_exit(func_name)
 *  is invoked during unloading of the kernel taking this function name as its parameter
 *
 */


static void __exit simple_exit(void)
{
	final_time = jiffies;/*store jiffies time during un-loading module*/
	printk("\n Removing this current kernel Bye !\n");
	printk("GCD of (3300,24): %lu\n", gcd(3300, 24));
	printk("Jiffies or total interrupts from system boot: %lu\n", final_time);
	printk("total time elapsed since module was first loaded: %lu\n\n", (final_time - initial_time) * 1 / HZ);
}

/**
 * Kernel module entry and exit points
 * Incase of module_exit it unregisters the module functionality from the kernel
 */

module_init(simple_init);
module_exit(simple_exit);
