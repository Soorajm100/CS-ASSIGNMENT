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
The above lines represent details regarding the software license, description of the module, and author. For our purposes, we do not depend on this information, but we include it because it is standard practice in developing kernel modules. This kernel module simple.c is compiled using the Makefile accompanying the source code with this project. To compile the module, enter the following on the command line:


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
