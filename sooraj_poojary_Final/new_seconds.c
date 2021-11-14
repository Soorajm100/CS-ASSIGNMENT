#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>
#include <asm/param.h>
#include <linux/jiffies.h>

/* Meta Information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sooraj m Poojary");
MODULE_DESCRIPTION("CS ASSIGNMENT PROC FILE FOR JIFFIES");

/**
 * @brief This function is called, when the module is loaded into the kernel
 */
#define BUFFER_SIZE 128
#define PROC_NAME "seconds"

ssize_t p_read(struct file *file, char __user *usr_buf,
size_t count, loff_t *pos);


static const struct proc_ops p_ops= {
	
	.proc_read = p_read,
};

static int __init simple_init(void) {
	/* creates the /proc/jiffies entry */
	proc_create(PROC_NAME, 0666, NULL, &p_ops);
	return 0;
}

/**
 * @brief This function is called, when the module is removed from the kernel
 */
static void __exit simple_exit(void) {
	
	/* removes the /proc/jiffies entry */
	remove_proc_entry(PROC_NAME, NULL);
}

/* Here in  this function is called each time /proc/jiffies is read */
ssize_t p_read(struct file *file, char __user *usr_buf,
size_t count, loff_t *pos)
{
int rv = 0;
char buffer[BUFFER_SIZE];
static int completed = 0;

if (completed) {
completed = 0;
return 0;
}

completed = 1;

rv = sprintf(buffer, "Seconds: %ld\n",jiffies/HZ);
/* copies kernel space buffer to user space usr buf */
copy_to_user(usr_buf, buffer, rv);
return rv;
}

module_init(simple_init);
module_exit(simple_exit);
