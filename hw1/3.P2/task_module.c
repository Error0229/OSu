#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A module about the task information");
MODULE_AUTHOR("catJAM");

static int pid;

static int task_show(struct seq_file *m, void *v) {
  struct task_struct *task;
  task = pid_task(find_vpid(pid), PIDTYPE_PID);
  if (task == NULL) {
    seq_printf(m, "No such process\n");
    return 0;
  }
  seq_printf(m, "name: %s, pid: [%d], state: %c\n", task->comm, task->pid,
             task_state_to_char(task));
  return 0;
}

static int task_open(struct inode *inode, struct file *file) {
  return single_open(file, task_show, NULL);
}

static ssize_t task_write(struct file *file, const char __user *buffer,
                          size_t count, loff_t *f_pos) {
  char *buf;
  buf = kmalloc(count, GFP_KERNEL);
  if (copy_from_user(buf, buffer, count)) {
    kfree(buf);
    return -EFAULT;
  }
  sscanf(buf, "%d", &pid);
  kfree(buf);
  return count;
}

static int __init task_module_init(void) {
  static const struct proc_ops task_fops = {
      .proc_open = task_open,
      .proc_read = seq_read,
      .proc_lseek = seq_lseek,
      .proc_release = single_release,
      .proc_write = task_write,
  };
  proc_create("pid", 0666, NULL, &task_fops);
  printk(KERN_INFO "/proc/pid created\n");
  return 0;
}

static void __exit task_module_exit(void) {
  remove_proc_entry("pid", NULL);
  printk(KERN_INFO "/proc/pid removed\n");
}

module_init(task_module_init);
module_exit(task_module_exit);
