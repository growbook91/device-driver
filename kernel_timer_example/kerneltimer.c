#include <linux/module.h>//
#include <linux/kernel.h>//
#include <linux/init.h>//
#include <linux/errno.h>//
//file operation 구조체가 선언됨.
#include <linux/fs.h>//
#include <linux/uaccess.h>
#include <asm/io.h>
#include <linux/slab.h>

#include <linux/time.h>
#include <linux/timer.h>

#define TIME_STEP       (2*HZ)

typedef struct
{
    struct timer_list timer;
    unsigned long led;
} __attribute__((packed)) KERNEL_TIMER_MANAGER;

static KERNEL_TIMER_MANAGER *ptrmng = NULL;


void kerneltimer_timeover(unsigned long arg);

void kerneltimer_registertimer(KERNEL_TIMER_MANAGER *pdata, unsigned long timeover)
{
    timer_setup(&(pdata->timer), kerneltimer_timeover, 0);
    pdata->timer.expires    = get_jiffies_64() + timeover;
    add_timer(&(pdata->timer));
}

void kerneltimer_timeover(unsigned long arg)
{
    KERNEL_TIMER_MANAGER *pdata = NULL;

    if(arg)
    {
        pdata = (KERNEL_TIMER_MANAGER *) arg;

        // add a line that checks the status of led and call printk()
        if(pdata->led == 1){
            printk("kereneltimer : LED is ON\n");
        }
        else{
            printk("kereneltimer : LED is OFF\n");
        }
        
        pdata->led = ~(pdata->led);

        kerneltimer_registertimer(pdata, TIME_STEP);
    }
}

int kerneltimer_init(void){
    ptrmng = kmalloc(sizeof(KERNEL_TIMER_MANAGER), GFP_KERNEL);
    if(ptrmng == NULL) return -ENOMEM;

    memset(ptrmng, 0, sizeof(KERNEL_TIMER_MANAGER));

    ptrmng->led = 0;
    kerneltimer_registertimer(ptrmng, TIME_STEP);

    return 0;
}

void kerneltimer_exit(void){
    if(ptrmng != NULL){
        del_timer(&(ptrmng->timer));
        kfree(ptrmng);
    }
}

module_init(kerneltimer_init);
module_exit(kerneltimer_exit);

MODULE_LICENSE("Dual BSD/GPL");


