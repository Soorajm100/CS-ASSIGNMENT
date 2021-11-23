/*
 * new_seconds.c
 * Kernel program to show the time elapsed in seconds between loading and unloading moduleby 
 * communicating through proc file system
 *
 * Operating system concepts - 10th Edition 
 * Written by Sooraj  Poojary
 * 
 */

#include <linux/init.h>           /*header file includes all the things related to__initpart*/
#include <linux/kernel.h>         /*header file for KERN_ALERT and KERN_INFO*/
#include <linux/module.h>         /*header file for module_init and module_exit*/
#include <linux/proc_fs.h>        /*header file for proc file system and its functionalities*/
#include <asm/uaccess.h>          /*header file where copy_to_user() is defined*/
#include <asm/param.h>            /*header file to access HZ which determine frequency of time interrupt */
#include <linux/jiffies.h>        /*header file for jiffies which maintains the number of timer interrupts that
have occurred since the system was booted.*/


/* Meta Information */
MODULE_LICENSE("GPL");                /* use any other system libraries running under GPL license*/
MODULE_AUTHOR("Sooraj m Poojary");    /* macro to define module author name*/
MODULE_DESCRIPTION("CS ASSIGNMENT PROC FILE FOR SECONDS");  /*macro to define the module description*/



/**
 * @brief This function is called, when the module is loaded into the kernel
*/


#define BUFFER_SIZE 128                     /*defines the buffer size of 128 bytes used by the program */
#define PROC_NAME "seconds"                  /*here the proc file gets its name*/



/**
 * declaration of p_read 
 *
 * The funs * This function is called repeatedly until it returns 0, so
 * there must be logic that ensures it ultimately returns 0
 * once it has collected the data that is to go into the
 * corresponding /proc file.
 */



 /**
  *  to store values of jiffies during the loading and unloading of kernel modules
  **/
unsigned long int initial_time , final_time ;

ssize_t p_read(struct file *file, char __user *usr_buf,
               size_t count, loff_t *pos);
long int i;
static const struct proc_ops p_ops = {

    .proc_read = p_read,
};

/**
 * This function is invoked when module is loaded in the kernel
 */
static int __init simple_init(void)
{
    initial_time=jiffies;
    /* it will create the /proc/jiffies entry */
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
    printk(KERN_INFO "/proc/%s has been removed\n",PROC_NAME);

}

/**
 *  Here in  this function is called each time /proc/jiffies is read
 */
ssize_t p_read(struct file *file, char __user *usr_buf,
               size_t count, loff_t *pos)
{
    int rv = 0;
    char buffer[BUFFER_SIZE];   /*defining the buffer size of 128 bytes as defined by MACRO*/
    static int completed = 0;
    
    if (completed)       /* making sure that function is called repeadtedly until this returns 1*/
    {
        completed = 0;
        return 0;
    }

    completed = 1;
    /* the value of secondsstored in jiffies that is part of kernel-buffer space*/
    rv = sprintf(buffer, "Time elapsed since module was first loaded is: %ld\n", (final_time-initial_time) / HZ);
    /* copies kernel space buffer to user space usr buf */
    copy_to_user(usr_buf, buffer, rv);
    return rv;
}


/*
 * module entry and exit point
 * But in module_exit , it is the exit point to kernel module where it unregisters the module 
 * funtionality from the kernel
 *
 *
 */

module_init(simple_init);
module_exit(simple_exit);
