#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/hash.h>
#include <linux/gcd.h>
#include <asm/param.h>
#include <linux/jiffies.h>

int simple_init(void) {
    printk(KERN_INFO "Golden ratio: %llu\n", GOLDEN_RATIO_PRIME);
    printk(KERN_INFO "Loading kernel module...\n");
    printk(KERN_INFO "HZ: %d\n", HZ);
    printk(KERN_INFO "Jiffies: %lu\n", jiffies);

    return 0;
}

void simple_exit(void) {
    printk(KERN_INFO "%lu\n", gcd(3300, 24));
    printk(KERN_INFO "Jiffies: %lu\n", jiffies);
    printk(KERN_INFO "Removing kernel module...\n");
}

module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple module");
MODULE_AUTHOR("Daniel");
