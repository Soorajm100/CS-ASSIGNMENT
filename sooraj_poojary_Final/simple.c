#include <linux/module.h>
#include <linux/init.h>
#include <linux/hash.h>
#include <linux/gcd.h>
#include <asm/param.h>
#include <linux/jiffies.h>
/* Meta Information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("CS ASSIGNMENT");
MODULE_DESCRIPTION("Simple Module");

/**
 * @brief This function is called, when the module is loaded into the kernel
 */
static int __init simple_init(void)
{
    printk("Loading the Kernel Module!\n");
    printk("GOLDEN RATIO PRIME: %lu\n", GOLDEN_RATIO_PRIME);
    printk("JIFFIES: %lu HZ: %d\n", jiffies, HZ);
    return 0;
}

/**
 * @brief This function is called, when the module is removed from the kernel
 */
static void __exit simple_exit(void)
{
    printk("Removing the Kernel Bye!\n");
    printk("GCD(3300,24): %lu\n", gcd(3300, 24));
    printk("JIFFIES: %lu\n", jiffies);
}

module_init(simple_init);
module_exit(simple_exit);
