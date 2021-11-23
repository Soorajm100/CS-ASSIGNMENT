## CS252 -ASSIGNMENT KERNEL MODULES

<b>Name : </b> Sooraj M Poojary  <br/>
<b>Roll no : </b> 191ME184      <br/>
<b>Batch : </b> M2    <br/>
<b>Branch : </b> Mechanical Engineering    <br/>
<b>Type of projects: </b> 1 Medium level Question Chapter 2 Project 1 - Individual   <br/>

This assignments mainly deals with operations performed  with kernel modules.

## Introduction



* In this project, we  will be learning how to create a kernel module and load it into the Linux kernel. We have to use  the terminal application to compile the programs, 
* We will have to enter commands on the command line to manage the modules in the kernel.
* we will discover, the advantage of developing kernel modules is that it is a relatively easy method of interacting with the kernel, thus allowing us  to write programs that directly invoke kernel functions



## Environment Setup 
 
* I used  Oracle Virtual Box to install ubutnu in it.
* First download the set up file for VM Box
* https://www.virtualbox.org/wiki/Downloads
* After setting up VM Box 
* Download Ubuntu 20.04 LTS from 
* https://ubuntu.com/download/desktop
* Follow the instruction given in following youtube vedio
* https://youtu.be/x5MhydijWmc
* Also after setting up ubuntu update all the packages required .
* I  refereshed my understanding  about linux commands from :
* https://maker.pro/linux/tutorial/basic-linux-commands-for-beginners
* You are all set for Project  👍


## Issues -Faced

* Initially it was difficult to understand but after reading the manual it become quite easy. 
* Took help from online youtube vedios and got deep knowledge .
* Faced issues while compiling so refferred stack overflow  for solutions.
* Did some research understood the code provided in the text or manual and modified it.



## Working-Questions

* Print out the value of GOLDEN RATIO PRIME in the simple init() function.
* Print out the greatest common divisor of 3,300 and 24 in the simple exit() function
* Print out the values of jiffies and HZ in the simple init() function.
* Print out the value of jiffies in the simple exit() function.
* Design a kernel module that creates a /proc file named /proc/jiffies that reports the current value of jiffies when the /proc/jiffies file is read, such as with the command cat /proc/jiffies.Be sure to remove /proc/jiffies when the module is removed.
*  Design a kernel module that creates a proc file named /proc/seconds that reports the number of elapsed seconds since the kernel module was loaded. This will involve using the value of jiffies as well as the HZ rate. When a user enters the commandcat /proc/seconds your kernel module will report the number of seconds that have elapsed since the kernel module was first loaded. Be sure to remove /proc/seconds when the module is removed.



## Creation of Kernel Modules

The first and primary task is to create and load the kernel module into the kernel.we will be able to list all the kernel module by using the command 

                   lsmod
The command will list  all the kernel modules providing description by three columns that is name , size ,used by 

The following code is available we have to make a file called simple.c and paste the code given from the textbook (Reference:<b> Operating system Concepts Abraham Silberschatz , Peter Galvin , Greg Gagne </b>)

```c

#include <linux/module.h>
#include <linux/init.h>

/* Meta Information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("SOORAJ POOJARY CS ASSIGNMENT");
MODULE_DESCRIPTION("Simple Module");

/**
 * @brief This function is called, when the module is loaded into the kernel
 */
static int __init simple_init(void) {
	printk("Loading the Kernel Module!\n");
	return 0;
}

/**
 * @brief This function is called, when the module is removed from the kernel
 */
static void __exit simple_exit(void) {
	printk("Removing the Kernel Bye!\n");
}

module_init(simple_init);
module_exit(simple_exit);
```

* Here we will find the function simple_init() which is the module entry point, it  represents the function that is invoked when the module is loaded into the kernel. Similarly, the simple_exit() function is the module exit point—the function that is called when the module is removed from the kernel.
* The module entry point function must return an integer value, with 0 representing success and any other value representing failure. The module exit point function returns void. Neither the module entry point nor the module exit point is passed any parameters. The two following macros are used for registering the module entry and exit points with the kernel:
 
                   module_init()
                
                   module_exit()

* we notice that how both the module entry and exit point functions make calls to the printk() function. printk() is the kernel equivalent of printf(), yet its output is sent to a kernel log buffer its contents could  be read by the dmesg command. One difference between printf() and printk() is that printk() allows us to specify a priority flag whose values are given in the <linux/printk.h> include file. 

*    
```c

        MODULE LICENSE(), MODULE DESCRIPTION(), and MODULE AUTHOR() 
 ```
The above lines represent details regarding the software license, description of the module, and author. For our purposes, we do not depend on this information, but we include it because it is standard practice in developing kernel modules. This kernel module simple.c is compiled using the Makefile accompanying the source code with this project.


## Creation of Makefile

* Creation of Makefile includes following make commands

```c


obj-m += simple.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean



```


* After the creation of Makefile we type the command  

                                 make
* This compilation  produces several files. The file simple.ko represents the compiled kernel module. 
   The following step illustrates inserting this module into the Linux kernel.
* Next step is to load the module simple.ko.

* So we use the command 
            
      sudo insmod simple.ko
  This command loads the module and we can check whether the module has loaded, enter the 
                                
      lsmod 
  command and search for the module simple. Recall that the module entry point is invoked when the module is inserted into the kernel. To check the contents of this message in the kernel log buffer, enter the command 
      
      dmesg | tail 

  This generates the message Loading Kernel Modules.
  
  
  ## Part 2 of Assignment

* We can add the necessary header files given in the textbook and claculate the time as well as jiffies and HZ as well.
* As kernel modules are running within the kernel, it is possible to obtain values and call functions that are available only in the kernel and not to regular user applications. For example, the Linux include file <linux/hash.h> defines several hashing functions for use within the kernel. This file also defines the constant value GOLDEN RATIO PRIME
* The logic for the different variables and instructions must be followed and printed that is GOLDEN_RATIO_NUMBER and Jiffies and HZ as well GCD.

* <b> Then the edited simple.c file must be compiled by make and then loaded and executed by dmesg </b>
  
 * It prints all the necessary values.



## Part 3   Creation of proc files

* Here we create the proc files by just editing the source code given from the textbook

* The /proc file system is a “pseudo” file system that exists only in kernel mem-
ory and is used primarily for querying various kernel and per-process statistics.

* Here I used **simple_init and simple_exit** as the entry and exit point of the module.

* Here in  the first file we define the proc name to be jiffies. Name the file as suitable i named it as new
* The second file proc name we define as seconds. Since we call it by cat command.Name the file as suitable i named it as new_seconds
* Slight changes has to be made static struct function as i faced error i changed the data type to static const struct proc_ops and defined the variable p_read for proc_ops took reference from **stackoverflow**





## Execution of proc files

* In this we have to to print the values of jiffies.
* with sprintf function we will be able to print the values of buffer which was stored in rv variable.
* The program prints the values of jiffies and time respectively.

###  The Proceedure to execute the program:

* Type the command 
      
      make 
  to compile the file change the make file accordingly by changing the code so that it could compile the right file.

 * Load the file. In my case the filename is new.ko so

        sudo insmod new.ko  

 * Make sure to check whether the file has been loaded to kernel or not 
               
               lsmod | grep new

 * After that we type the command as 

               cat /proc/jiffies
 * It prints the jiffies 

 * Similar proceedure can be done for new_seconds.c file in order to print the seconds.



