#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <asm/uaccess.h>
#include <linux/jiffies.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

#define PROC_NAME "seconds"

static unsigned long initial;

static int my_proc_open(struct inode *inode, struct file *file); 

static int my_proc_show(struct seq_file *f, void *v);

static const struct proc_ops my_proc_ops = {
    .proc_open = my_proc_open,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_release = single_release
};

int proc_init(void) {
    printk(KERN_INFO "Initializing seconds module\n");
    proc_create(PROC_NAME, 0666, NULL, &my_proc_ops);
    initial = jiffies;
    printk(KERN_INFO "Created seconds module with initial jiffies value of %lu\n", jiffies);
    return 0;
}

void proc_exit(void) {
    printk(KERN_INFO "Removing seconds module\n");
    remove_proc_entry(PROC_NAME, NULL);
    printk(KERN_INFO "Successfully removed seconds module\n");
}

static int my_proc_show(struct seq_file *f, void *v) {
    printk(KERN_INFO "Outputting seconds to /proc\n");
    unsigned long elapsed = jiffies - initial;
    unsigned long seconds = elapsed / HZ;
    printk(KERN_INFO "jiffies: %lu\n", jiffies);
    printk(KERN_INFO "initial: %lu\n", initial);
    printk(KERN_INFO "elapsed: %lu\n", elapsed);
    printk(KERN_INFO "HZ: %d\n", HZ);
    seq_printf(f, "%lu\n", seconds);
    printk(KERN_INFO "Outputted seconds to /proc\n");
    return 0;
}

static int my_proc_open(struct inode *inode, struct file *file) {
    printk(KERN_INFO "Opening seconds /proc\n");
    return single_open(file, my_proc_show, NULL);
}

module_init(proc_init);
module_exit(proc_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Seconds module");
MODULE_AUTHOR("Daniel");

