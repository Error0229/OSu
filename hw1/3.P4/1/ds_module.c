#include <linux/list.h>
#include <linux/module.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A module that implement linked list");
MODULE_AUTHOR("catJAM");

struct color {
  int red;
  int green;
  int blue;
  struct list_head list;
};

static LIST_HEAD(color_list);
static int __init ds_module_init(void) {
  struct color *violet, *azure, *falu, *indigo;
  violet = kmalloc(sizeof(struct color), GFP_KERNEL);
  violet->red = 138;
  violet->green = 226;
  violet->blue = 43;
  azure = kmalloc(sizeof(struct color), GFP_KERNEL);
  azure->red = 0;
  azure->green = 123;
  azure->blue = 167;
  falu = kmalloc(sizeof(struct color), GFP_KERNEL);
  falu->red = 128;
  falu->green = 24;
  falu->blue = 24;
  indigo = kmalloc(sizeof(struct color), GFP_KERNEL);
  indigo->red = 75;
  indigo->green = 0;
  indigo->blue = 130;
  INIT_LIST_HEAD(&violet->list);
  INIT_LIST_HEAD(&azure->list);
  INIT_LIST_HEAD(&falu->list);
  INIT_LIST_HEAD(&indigo->list);

  list_add_tail(&violet->list, &color_list);
  list_add_tail(&azure->list, &color_list);
  list_add_tail(&falu->list, &color_list);
  list_add_tail(&indigo->list, &color_list);

  struct color *ptr;
  list_for_each_entry(ptr, &color_list, list) {
    printk(KERN_INFO "red: %d, green: %d, blue: %d\n", ptr->red, ptr->green,
           ptr->blue);
  }
  return 0;
}

static void __exit ds_module_exit(void) {
  struct color *ptr, *next;
  list_for_each_entry_safe(ptr, next, &color_list, list) {
    list_del(&ptr->list);
    kfree(ptr);
  }
  printk(KERN_INFO "ds module removed\n");
}

module_init(ds_module_init);
module_exit(ds_module_exit);
