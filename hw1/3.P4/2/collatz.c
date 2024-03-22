#include <linux/init.h>
#include <linux/list.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A module that implement collatz sequence");
MODULE_AUTHOR("👾");

static int start = 25;
module_param(start, int, 0);

struct collatz {
  int value;
  struct list_head list;
};
static LIST_HEAD(collatz_list);
static int __init collatz_module_init(void) {
  int now = start;
  while (now != 1) {
    struct collatz *new;
    new = kmalloc(sizeof(struct collatz), GFP_KERNEL);
    new->value = now;
    INIT_LIST_HEAD(&new->list);
    list_add_tail(&new->list, &collatz_list);
    if (now % 2 == 0) {
      now /= 2;
    } else {
      now = 3 * now + 1;
    }
  }
  struct collatz *new;
  new = kmalloc(sizeof(struct collatz), GFP_KERNEL);
  new->value = now;
  INIT_LIST_HEAD(&new->list);
  list_add_tail(&new->list, &collatz_list);

  struct collatz *ptr;
  list_for_each_entry(ptr, &collatz_list, list) {
    printk(KERN_INFO "value: %d\n", ptr->value);
  }
  return 0;
}

static void __exit collatz_module_exit(void) {
  struct collatz *ptr, *next;
  list_for_each_entry_safe(ptr, next, &collatz_list, list) {
    list_del(&ptr->list);
    kfree(ptr);
  }
  printk(KERN_INFO "collatz module removed\n");
}

module_init(collatz_module_init);
module_exit(collatz_module_exit);
