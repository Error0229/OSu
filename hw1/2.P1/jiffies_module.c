#include <linux/init.h>
#include <linux/jiffies.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A module that shows the current jiffie and the seconds "
                   "since the start of the module");
MODULE_AUTHOR("👾");
static unsigned long start_jiffies;
static int jiffies_show(struct seq_file *m, void *v) {
  seq_printf(m, "The current jiffies is %llu\n", (unsigned long long)jiffies);
  return 0;
}

static int jiffies_open(struct inode *inode, struct file *file) {
  return single_open(file, jiffies_show, NULL);
}
static int seconds_show(struct seq_file *m, void *v) {
  seq_printf(m, "Already pass %lu seconds since the module installed\n",
             (jiffies - start_jiffies) / HZ);
  return 0;
}
static int seconds_open(struct inode *inode, struct file *file) {
  return single_open(file, seconds_show, NULL);
}
static int __init jiffies_module_init(void) {
  // Create the /proc/jiffies entry
  static const struct proc_ops jiffies_fops = {
      .proc_open = jiffies_open,
      .proc_read = seq_read,
      .proc_lseek = seq_lseek,
      .proc_release = single_release,
  };
  proc_create("jiffies", 0, NULL, &jiffies_fops);
  printk(KERN_INFO "/proc/jiffies created\n");
  // Create the /proc/seconds
  static const struct proc_ops seconds_fops = {
      .proc_open = seconds_open,
      .proc_read = seq_read,
      .proc_lseek = seq_lseek,
      .proc_release = single_release,
  };
  proc_create("seconds", 0, NULL, &seconds_fops);
  printk(KERN_INFO "/proc/seconds created\n");
  start_jiffies = jiffies;
  return 0;
}

static void __exit jiffies_module_exit(void) {
  // Remove the /proc/jiffies entry
  remove_proc_entry("jiffies", NULL);
  printk(KERN_INFO "/proc/jiffies removed\n");
  // Remove the /proc/seconds entry
  remove_proc_entry("seconds", NULL);
  printk(KERN_INFO "/proc/seconds removed\n");
}

module_init(jiffies_module_init);
module_exit(jiffies_module_exit);
