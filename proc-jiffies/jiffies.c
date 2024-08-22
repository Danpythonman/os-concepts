#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
//#include <asm/param.h>
#include <asm/uaccess.h>
#include <linux/jiffies.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

#define PROC_NAME "jiffies"

static int my_proc_open(struct inode *inode, struct file *file); 

static int my_proc_show(struct seq_file *f, void *v);

static const struct proc_ops my_proc_ops = {
    .proc_open = my_proc_open,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_release = single_release
};

int proc_init(void) {
    printk(KERN_INFO "Initializing jiffies module\n");
    proc_create(PROC_NAME, 0666, NULL, &my_proc_ops);
    printk(KERN_INFO "Created jiffies module\n");
    return 0;
}

void proc_exit(void) {
    printk(KERN_INFO "Removing jiffies module\n");
    remove_proc_entry(PROC_NAME, NULL);
    printk(KERN_INFO "Successfully removed jiffies module\n");
}

static int my_proc_show(struct seq_file *f, void *v) {
    printk(KERN_INFO "Outputting jiffies to /proc\n");
    seq_printf(f, "%lu\n", jiffies);
    printk(KERN_INFO "Outputted jiffies to /proc\n");
    return 0;
}

static int my_proc_open(struct inode *inode, struct file *file) {
    printk(KERN_INFO "Opening jiffies /proc\n");
    return single_open(file, my_proc_show, NULL);
}

module_init(proc_init);
module_exit(proc_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Jiffies module");
MODULE_AUTHOR("Daniel");

