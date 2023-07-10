#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/errno.h>
//file operation 구조체가 선언됨.
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <asm/io.h>
#include <linux/slab.h>

#define SKELETON26_NAME "SKELETON26"
#define SKELETON26_MAJOR 240




// Since the arguments denote information of a device file, 
// sys_open() could distinguish and call skeleton26_open().
int skeleton26_open(struct inode *inode, struct file *filp){
    printk("SKELETON26: skeleton26_open() is called..\n");

    printk("SKELETON26: \t Major number = %d \n", MAJOR(inode->i_rdev));
    printk("SKELETON26: \t Minor number = %d \n", MINOR(inode->i_rdev));

    return 0;
}

int skeleton26_release(struct inode *inode, struct file *filp){
    printk("SKELETON26 : skeleton26_release() is called..\n");

    return 0;
}

// struct file is structure pointing file.
// 여기서 buf는 user application의 read에서 넣어준 그 buf이다.
ssize_t skeleton26_read(struct file *filp, char *buf, size_t count, loff_t *f_pos){
    char *dev_data = "ABCD";
    int err;
    // Copy data from kernel space to user space. Caller must check the specified block with access_ok before calling this function.
    // Returns number of bytes that could not be copied. On success, this will be zero.
    // from은 완전히 반대로 동작한다고 생각하면 될 것 같다.
    // 여기 예시에서는 dev_data에 있는 data를 buf로 count만큼 옮기는 것이다.
    // 아 copy_to_user와 put_user를 사용하는 이유는 드라이버에서는 buf에 직접 진입할 수 있는 게 아니기 때문이다. 
    // 디바이스 드라이버에서는 커널 메모리 공간을 사용하고 응용 프로그램은 user space를 사용하고 있기 때문에.
    if((err = copy_to_user(buf, dev_data, count)) < 0)
        return err;

    printk("SKELETON26: skeleton26_read() is called..\n");

    return count;
}

ssize_t skeleton26_write(struct file *filp, const char *buf, size_t count, loff_t *_pos){
    char *dev_data;
    int err;

    dev_data=kmalloc(count, GFP_KERNEL);

    if((err=copy_from_user(dev_data, buf, count)) < 0)
        return err;

    printk("SKELETON26: skeleton26_write() is called..\n");
    printk("SKELETON26: \t User write data = %s..\n", dev_data);

    kfree(dev_data);

    return count;
}

//file_operations 구조체가 character device driver와 user application을 연결하는 고리다. 
// user application이 저수준 파일 입출력 함수를 통해 device file에 접근하면 
// kernel은 등록된 character device의 file operations 구조체 정보를 참고하여 디바이스 파일에 접근한 함수에 대응하는 함수를 호출
struct file_operations skeleton26_fops = 
{
    .open       =   skeleton26_open,
    .release    =   skeleton26_release,
    .read       =   skeleton26_read,
    .write      =   skeleton26_write,
};

int skeleton26_init(void)
{
    int result;

    printk("SKELETON 26 : skeleton26_init() is called.. \n");

    result = register_chrdev(SKELETON26_MAJOR, SKELETON26_NAME, &skeleton26_fops);

    if(result < 0){
        printk("SKELETON26: \t Can't get major number");
        return result;
    }
    
    printk("SKELETON26 : SKELETON26_MAJOR=%d\n", SKELETON26_MAJOR);

    return 0;
}

void skeleton26_exit(void){
    unregister_chrdev(SKELETON26_MAJOR, SKELETON26_NAME);
}

module_init(skeleton26_init);
module_exit(skeleton26_exit);
MODULE_LICENSE("GPL");