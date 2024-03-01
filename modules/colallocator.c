#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/mm.h> // 包含get_zeroed_page函数声明的头文件
#include <asm/io.h>

#define DEFENCE 256
#define PAGE_SIZE 4096

unsigned long *pool;

static int __init my_init(void) {

    unsigned long phys_addr;

    pool = (unsigned long *)kmalloc(PAGE_SIZE * DEFENCE, GFP_ATOMIC); // 从物理内存中获取一个页面并清零
    if (!pool) {
        printk(KERN_ERR "Failed to allocate memory\n");
        return -ENOMEM;
    }

    printk(KERN_ERR "success to allocate \n");

    printk(KERN_INFO "Memory allocated at address: %p\n", pool);

    // 将虚拟地址转换为物理地址
    phys_addr = virt_to_phys(pool);

    printk(KERN_INFO "Virtual Address: %p, Physical Address: %lx\n", pool, phys_addr);

    kfree((unsigned long)pool); // 释放分配的页面

    return 0;
}

static void __exit my_exit(void) {
    if (pool) {
        kfree(pool); // 释放内存
        printk(KERN_INFO "Memory freed\n");
    }
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
