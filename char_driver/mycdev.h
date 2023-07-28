#include <linux/fs.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/kdev_t.h>
#include <linux/device.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/uaccess.h>

#define SUCCESS 0
#define FAILURE -1
#define NR_DEVICES 2
#define MAX_KERN_BUF_LEN 50

int cdev_major=0;
int cdev_first_minor=0;
int nr_devices=NR_DEVICES;

typedef struct my_chardev_priv {
    struct cdev cdev;
    struct class *my_cdev_class;
}my_chardev_priv_t;

static my_chardev_priv_t my_cdev_priv[NR_DEVICES];
static struct class *my_cdev_class=NULL;


static int my_cdev_uevent(
        struct device *dev,
        struct kobj_uevent_env *env);

static ssize_t mycdev_write(
        struct file *file,
        const char __user *user_buf,
        size_t count,
        loff_t *offset);

static ssize_t mycdev_read(struct file *file,
        char __user *user_buf,
        size_t count,
        loff_t *offset);

static long mycdev_ioctl(
        struct file *file,
        unsigned int cmd,
        unsigned long arg);

static int mycdev_release(
        struct inode *inode,
        struct file *file);

static int mycdev_open(
        struct inode *inode,
        struct file *file);

static void setup_mycdev(
        my_chardev_priv_t *mydev_priv,
        uint8_t index);


