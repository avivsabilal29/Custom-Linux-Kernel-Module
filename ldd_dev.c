#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h> // copy_to_user
#include <linux/cdev.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Aviv Sabilal <sabiluladiib29@gmail.com>");
MODULE_DESCRIPTION("Basic character device driver example");

#define DEVICE_NAME "sabilal_device"
static int major_number;
static struct cdev sabilal_cdev;

static char device_message[100] = "Hello from Sabilal Device!\n";

static ssize_t sabilal_read(struct file *file, char __user *buffer, size_t len, loff_t *offset) {
    size_t message_len = strlen(device_message);

    if (*offset >= message_len) {
        return 0; // EOF
    }

    if (len > message_len - *offset) {
        len = message_len - *offset; // Adjust length to available data
    }

    if (copy_to_user(buffer, device_message + *offset, len)) {
        return -EFAULT; // Error copying to user space
    }

    *offset += len;
    return len;
}

static ssize_t sabilal_write(struct file *file, const char __user *buffer, size_t len, loff_t *offset) {
    if (len > sizeof(device_message) - 1) {
        len = sizeof(device_message) - 1; // Limit message size
    }

    if (copy_from_user(device_message, buffer, len)) {
        return -EFAULT; // Error copying from user space
    }

    device_message[len] = '\0'; // Null-terminate string
    printk(KERN_INFO "sabilal_write: Received %zu bytes: %s\n", len, device_message);
    return len;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .read = sabilal_read,
    .write = sabilal_write,
};

static int __init sabilal_driver_init(void) {
    printk(KERN_INFO "Initializing Sabilal Driver...\n");

    // Register the character device
    major_number = register_chrdev(0, DEVICE_NAME, &fops);
    if (major_number < 0) {
        printk(KERN_ALERT "Failed to register device\n");
        return major_number;
    }

    printk(KERN_INFO "Sabilal Device registered with major number %d\n", major_number);
    printk(KERN_INFO "Use 'mknod /dev/%s c %d 0' to create device node\n", DEVICE_NAME, major_number);
    return 0;
}

static void __exit sabilal_driver_exit(void) {
    printk(KERN_INFO "Removing Sabilal Driver...\n");
    unregister_chrdev(major_number, DEVICE_NAME);
}

module_init(sabilal_driver_init);
module_exit(sabilal_driver_exit);
