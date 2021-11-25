/**
 *new.c
 * Operating system concepts - 10th Edition
 * Kernel program to show the values of jiffies by communication through the proc file system 
 * Written By Sooraj Poojary
 *
 *
 */


#include <linux/init.h>    /*header files includes all the things related to __init part*/ 
#include <linux/kernel.h>  /*header file for KERN_ALERT and KERN_INFO*/
#include <linux/module.h>   /*header file for modules and macros like module_init and module_exit*/
#include <linux/proc_fs.h>  /* header file for proc file system*/
#include <asm/uaccess.h>    /*header file where copy_to_user() defined */ 
#include <asm/param.h>      /* header file to access HZ which determines the frequency of time interrupt*/
#include <linux/jiffies.h>  /*header file to access jiffies variable which maintains timer interrupts that have occurred since the system was booted*/


/* Meta Information S*/

MODULE_LICENSE("GPL");                       /* To use the system libraries running under GPL license */ 
MODULE_AUTHOR("Sooraj m Poojary");           /*Macro represents the author author of kernel code */ 
MODULE_DESCRIPTION("PROGRAM OF PROC FILE FOR JIFFIES");   /* Macro contains description about the kernel program*/


/**
 *  Macros for Buffer size and Proc name
 */

#define BUFFER_SIZE 128                     /*defining buffer size to be used by this program*/
#define PROC_NAME "jiffies"                /*This is where the proc file will be given name*/

/** 
 * This funstion is repeatedly called until it return 0 ,so
 * there must be logic  that ensures it ulitmately returns 0
 * Once it has collected the data that is to go into the corresponding  /proc file.
 * function to read the kernel buffer
 */
ssize_t p_read(struct file *file, char __user *usr_buf,
               size_t count, loff_t *pos);

static const struct proc_ops p_ops = {
    
    .proc_read = p_read,
};

/**
 * This function is called when the module is loaded into the kernel 
 */
static int __init simple_init(void)
{
    /* it will create the /proc/jiffies entries  */
    proc_create(PROC_NAME, 0666, NULL, &p_ops);
    printk(KERN_INFO "/proc/%s has been created\n",PROC_NAME);
    return 0;
}

/**
 * @brief This function is called, when the module is removed from the kernel
 */
static void __exit simple_exit(void)
{
    
    /* it will remove the /proc/jiffies entry */
    remove_proc_entry(PROC_NAME, NULL);
    printk(KERN_INFO "/proc/%s removed\n",PROC_NAME);
}

/* *
 * This function is called each time /proc/jiffies is read 
 */
ssize_t p_read(struct file *file, char __user *usr_buf,
               size_t count, loff_t *pos)
{
    int rv = 0;
    char buffer[BUFFER_SIZE];
    static int completed = 0;

    if (completed)      /*To make sure this fucntion will be called repeatedly unilt it returns 1*/
    {
        completed = 0;
        return 0;
    }

    completed = 1;
    
    /*value of jiffies which is part of kernel buffer space*/
    rv = sprintf(buffer, "JIFFIES or  the total number of interrupts that have occured since the system boot is: %lu\n", jiffies);
    
    
    /* copies kernel space buffer to user space usr buf */
    copy_to_user(usr_buf, buffer, rv);
    return rv;
}

/**
 * module entry and exit points. 
 * But in module_exit it unregisters the module functionality from the kernel
 *
 * */
module_init(simple_init);
module_exit(simple_exit);
