#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Aviv Sabilal <sabiluladiib29@gmail.com>");
MODULE_DESCRIPTION("Basic read loadable kernel module");

static struct proc_dir_entry *custom_proc_node;

static ssize_t sabilal_read(struct file* file_pointer,
                    char *user_space_buffer,
                    size_t count,
                    loff_t* offset) {
    char message[] = "ACK!\n";
    size_t len = strlen(message);
    int result;
    printk("sabilal_driver_read \n");

    if(*offset >= len){
        return 0;
    }

    result = copy_to_user(user_space_buffer, message, len);

    *offset += len;
    return len;
}

struct proc_ops driver_proc_ops = {
    .proc_read = sabilal_read
};

static int sabilal_driver_init(void){
    printk("sabilal_driver_init entry \n");
    custom_proc_node = proc_create("sabilal_driver",
                                    0,
                                    NULL,
                                    &driver_proc_ops);
    if (custom_proc_node == NULL)
    {
        printk("sabilal_module_init Error\n");
        return -1;
    }
    
    printk("sabilal_driver_init exit \n");
    return 0;
}

static void sabilal_exit(void){
    // printk("Good, Bye form Kernel Aviv\n");
    printk("sabilal_exit entry \n");
    proc_remove(custom_proc_node);
    printk("sabilal_exit exit \n");
}



module_init(sabilal_driver_init); // We called C Macros
module_exit(sabilal_exit); // We called C Macros