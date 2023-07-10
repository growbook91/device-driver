#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>


static int __init my_init(void){
        printk("\033[1;31m""hello, kernel!\n""\033[0m");
        return 0;
}

static void __exit my_exit(void){
        printk("\033[1;31m""goodbye, kernel!\n""\033[0m");
}

module_init(my_init);
module_exit(my_exit);
