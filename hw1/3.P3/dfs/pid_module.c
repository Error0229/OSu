#include <linux/init.h>
#include <linux/init_task.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A module that iterate over all the process");
MODULE_AUTHOR("catJAM");
void DFS(struct task_struct *task) {
  struct task_struct *child;
  printk(KERN_INFO "name: %s, pid: [%d], state: %c\n", task->comm, task->pid,
         task_state_to_char(task));
  list_for_each_entry(child, &task->children, sibling) { DFS(child); }
}

static int __init pid_module_init(void) {
  // use for_each_process to print all the pids
  printk(KERN_INFO "pid module created\n");
  DFS(&init_task);
  return 0;
}

static void __exit pid_module_exit(void) {
  printk(KERN_INFO "pid module removed\n");
}
module_init(pid_module_init);
module_exit(pid_module_exit);
