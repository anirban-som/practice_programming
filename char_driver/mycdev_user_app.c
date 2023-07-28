#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdint.h>
#include <unistd.h>

#define CDEV_FILE "/dev/mychar_dev-0"
#define SUCCESS 0
#define FAILURE -1
#define MAX_BUF_LEN 50
int main(void)
{
    int cdev_desc=0, ret=0;
    uint8_t read_buf[MAX_BUF_LEN]={0};
    char *user_data="Hello Buddy! I am from user space";

    cdev_desc = open(CDEV_FILE, O_WRONLY, 0644);
    if (cdev_desc < 0) {
        perror("can not open device file\n");
        return FAILURE;
    }
    ret = write(cdev_desc, user_data, strlen(user_data));
    if (ret < 0) {
        perror("error in writing to char device\n");
        return FAILURE;
    }
    close(cdev_desc);

    cdev_desc = open(CDEV_FILE, O_RDONLY);
    if (cdev_desc < 0) {
        perror("can not open device file\n");
        return FAILURE;
    }
    ret = read(cdev_desc, read_buf, (MAX_BUF_LEN-1));
    if (ret < 0) {
        perror("error in reading from char device\n");
        return FAILURE;
    }
    printf("bytes read from char device=[%s]\n", read_buf);
    close(cdev_desc);

    return SUCCESS;
}
