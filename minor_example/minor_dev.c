#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/errno.h>
// file operation 구조체가 선언됨.
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <asm/io.h>
#include <linux/slab.h>

#define MINOR_DEV_NAME "minordev"
#define MINOR_DEV_MAJOR 240

int minor0_open(struct inode *inode, struct file *filp)
{
    printk("call minor0_open\n");
    return 0;
}

ssize_t minor0_write(struct file *filp, const char *buf, size_t count, loff_t *f_pos)
{
    unsigned char status;
    int loop;

    for (loop = 0; loop < count; loop++)
    {
    }

    return count;
}

int minor0_release(struct inode *inode, struct file *filp)
{
    printk("call minor0_release\n");
    return 0;
}

int minor1_open(struct inode *inode, struct file *filp)
{
    printk("call minor1_open\n");
    return 0;
}

ssize_t minor1_read(struct file *filp, const char *buf, size_t count, loff_t *f_pos)
{
    unsigned char status;
    int loop;

    for (loop = 0; loop < count; loop++)
    {
    }

    return count;
}

int minor1_release(struct inode *inode, struct file *filp)
{
    printk("call minor1_release\n");
    return 0;
}

struct file_operations minor0_fops = 
{
    .owner      = THIS_MODULE,
    .write      = minor0_write,
    .open       = minor0_open,
    .release    = minor0_release,
};

struct file_operations minor1_fops = 
{
    .owner      = THIS_MODULE,
    .read      = minor1_read,
    .open       = minor1_open,
    .release    = minor1_release,
};

int minor_open(struct inode *inode, struct file *filp){
    prinkt("call minor open\n");
    switch (MINOR(inode->i_rdev))
    {
    case 1:
        filp->f_op = &minor0_fops;
        break;
    
    case 2:
        filp->f_op = &minor0_fops;
        break;

    default:
        return -ENXIO;
    }
}

struct file_operations minor_fops =
{
    .owner  = THIS_MODULE,
    .open   = minor_open,
};

int minor_init(void){
    int result;

    result = register_chrdev(MINOR_DEV_MAJOR, MINOR_DEV_NAME, &minor_fops);

    if(result < 0) return result;

    return 0;
}

void minor_exit(void){
    unregister_chrdev(MINOR_DEV_MAJOR, MINOR_DEV_NAME);
}

module_init(minor_init);
module_exit(minor_exit);

MOUDLE_LICENSE("Dual BSD/GPL");
