#include "mycdev.h"

MODULE_LICENSE("GPL");MODULE_AUTHOR("Anirban Som");
MODULE_DESCRIPTION("Simple char driver for practice purpose");


static int my_cdev_uevent(
        struct device *dev,
        struct kobj_uevent_env *env)
{
    add_uevent_var(env, "DEVMODE=%#o", 0666);
    return 0;
}

static ssize_t mycdev_write(
        struct file *file,
        const char __user *user_buf,
        size_t count,
        loff_t *offset)
{
    uint8_t kern_buf[MAX_KERN_BUF_LEN]={0};
    
    uint8_t len_to_copy=0;

    len_to_copy = (count < MAX_KERN_BUF_LEN) ? count : (MAX_KERN_BUF_LEN - 1);
    if (copy_from_user(kern_buf, user_buf, len_to_copy)) {
        printk("%s: Error in copying from user\n", __func__);
        return -EFAULT;
    }

    printk("date received from user=[%s] \n", kern_buf);

    return len_to_copy;
}

static ssize_t mycdev_read(struct file *file,
        char __user *user_buf,
        size_t count,
        loff_t *offset)
{
    uint8_t *kern_buf = "Hello Champ! I am from char device!\n";
    size_t buflen = strlen(kern_buf);
    if (count > buflen) {
        count = buflen;
    }
    if (copy_to_user(user_buf, kern_buf, count)) {
        printk("%s: failed to copy to user\n", __func__);
        return -EFAULT;
    }

    return count;
}

static long mycdev_ioctl(
        struct file *file,
        unsigned int cmd,
        unsigned long arg)
{
    printk(KERN_ALERT "Anirban: %s\n", __func__);
    return SUCCESS;
}

static int mycdev_release(
        struct inode *inode,
        struct file *file)
{
    printk(KERN_ALERT "Anirban: %s\n", __func__);
    return SUCCESS;
}

static int mycdev_open(
        struct inode *inode,
        struct file *file)
{
    printk(KERN_ALERT "Anirban: %s\n", __func__);
    return SUCCESS;
}

static const struct file_operations mycdev_fops = {
    .owner = THIS_MODULE,
    .open = mycdev_open,
    .release = mycdev_release,
    .read = mycdev_read,
    .write = mycdev_write,
    .unlocked_ioctl = mycdev_ioctl,
};

static void setup_mycdev(
        my_chardev_priv_t *mydev_priv,
        uint8_t index)
{
    cdev_init(&mydev_priv[index].cdev, &mycdev_fops);
    mydev_priv[index].cdev.owner = THIS_MODULE;
    cdev_add(&mydev_priv[index].cdev, MKDEV(cdev_major, index), 1);
    device_create(my_cdev_class, NULL, MKDEV(cdev_major, index), NULL, "mychar_dev-%d", index);
}

static int __init my_char_dev_init(void)
{
    dev_t my_cdev;
    int result=SUCCESS, i=0;
    printk(KERN_ALERT "inside %s\n", __func__);

    if (cdev_major) {
        my_cdev = MKDEV(cdev_major, cdev_first_minor);
        result = register_chrdev_region(my_cdev, nr_devices, "my_char_dev");
    } else {
        result = alloc_chrdev_region(&my_cdev, cdev_first_minor, nr_devices, "my_char_dev");
        cdev_major = MAJOR(my_cdev);
    }
    if (result != 0) {
        printk(KERN_WARNING "%s: cannot get major=[%d]\n", __func__, cdev_major);
        return result;
    }

    my_cdev_class = class_create(THIS_MODULE, "my_char_dev");
    my_cdev_class->dev_uevent = my_cdev_uevent;

    for (i=0; i<nr_devices; i++) {
        setup_mycdev(&my_cdev_priv[i], i);
    }

    return result;
}

static void __exit my_char_dev_exit(void)
{
    uint8_t i=0;

    printk(KERN_ALERT "%s:%d\n", __func__, __LINE__);
    for(i=0; i<nr_devices; i++) {
        device_destroy(my_cdev_class, MKDEV(cdev_major, i));
    }
    class_unregister(my_cdev_class);
    printk(KERN_ALERT "%s:%d\n", __func__, __LINE__);
    class_destroy(my_cdev_class);

    unregister_chrdev_region(MKDEV(cdev_major, 0), MINORMASK);
    printk(KERN_ALERT "%s:%d\n", __func__, __LINE__);
}


module_init(my_char_dev_init);
module_exit(my_char_dev_exit);
