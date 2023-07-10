#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
//open함수 포함
#include <fcntl.h>
#include <unistd.h>

#define TEXT_LEN 5

int main(){
    static char buf[1024];
    int fd;
 
    if ((fd = open("/dev/SKELETON26", O_RDWR)) < 0) {
		perror("open error");
    }
 
    if (write(fd, "hello", TEXT_LEN) < 0) {
		perror("write error");
    }
 
    if (read(fd, buf, TEXT_LEN) < 0) {
		perror("read error");
    } else {
        printf("%s\n", buf);
    }
 
    if (close(fd) != 0) {
		perror("close error");
    }
}