/**
 * simple.c
 * A kernel program to load and unload modules to kernel
 *Operating system Concepts -10th Edition 
 * Written by Sooraj Poojary
 *
 *
 */


#include <linux/module.h>        /*header file for module_init and module_exit defined*/
#include <linux/init.h>          /*header file for all things related to __init part*/
#include <linux/hash.h>          /*header file for  hashing functions which has constant value GOLDEN_RATIO_PRIME*/
#include <linux/gcd.h>           /* header file used to access gcd function */
#include <asm/param.h>           /*header file to access HZ or the frequency of time interrupt*/
#include <linux/jiffies.h>       /*header file to access global jiffies variable which maintains timer interrupts*/


/* Meta Information */
MODULE_LICENSE("GPL");                               /*to use system libraries under GPL */
MODULE_AUTHOR("SOORAJ POOJARY");                     /*macro to represent the author*/
MODULE_DESCRIPTION("PROGRAM TO PRINT GOLDEN_RATIO JIFFIES GCD BASICALLY TO CREATE AND INSERT KERNEL MODULE");  /*macro represents description of module*/


/**
 * to store the jiffies values during the loading and unloading of module
 *
 *
 */
unsigned long int initial_time , final_time;

/**
 * @brief This function is called, when the module is loaded into the kernel that is when module_init is invoked
 * .module_init takes the following fucntion name as parameter and performs next operations.
 *
 */

static int __init simple_init(void)
{   /*printing the necessary variables and constant values*/
    initial_time = jiffies; /*stores jiffies value during loading kernel module*/
    printk("Loading the Kernel Module!\n");
    printk("GOLDEN RATIO PRIME which is a constant value: %llu\n", GOLDEN_RATIO_PRIME);
    printk("JIFFIES or total interrupt from  system boot: %lu\n HZ or the frequency of the timer interrupt: %d\n", jiffies, HZ);
    return 0;
}

/**
 * @brief This function is called, when the module is removed from the kernel. That is when module_exit is invoked. * It takes the function name as parameter and performs the next operations
 *
 */
static void __exit simple_exit(void)
{   /* prints necessary variables*/
    final_time = jiffies;  /*stores the *stores jiffies value during un-loading kernel module*/
    printk("Removing the Kernel Bye!\n");
    printk("GCD of (3300,24): %lu\n", gcd(3300, 24));
    printk("JIFFIES or total interrupts from system boot: %lu\n", jiffies);
    printk("total time elapsed since the module first loaded is: %lu\n\n ",(final_time-initial_time)/HZ);
}

/**
 * Kernel module entry and exit points
 * Incase of module_exit it unregisters the module functionality from the kernel 
 */
module_init(simple_init);
module_exit(simple_exit);
