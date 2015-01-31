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

static char * name = "UNKNOWN";
static int howmany = 1;

MODULE_DESCRIPTION("Module \"hello word\" pour noyau 2.6");
MODULE_AUTHOR("Julien Sopena, LIP6");
MODULE_LICENSE("GPL");

module_param(name, charp, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP );
MODULE_PARM_DESC(name, "Your Name");
module_param(howmany, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(howmany, "How Many");



static int hello_init(void)
{
  int i = 0;

  struct list_head * l;
  struct list_head * next;
  //printk(KERN_ALERT "Begin first loop , %p\n", next);
  /*list_for_each(l, next) {
  	i++;
  }
  printk(KERN_ALERT "end first loop , %p\n", next);

  printk(KERN_ALERT "First, %d\n", i);*/

  printk(KERN_ALERT "unlink module\n");
  list_del(&(THIS_MODULE->list));
  printk(KERN_ALERT "delete kobj\n");
  kobject_del(&(THIS_MODULE->mkobj.kobj));
  printk(KERN_ALERT "unlink kobj\n");
  list_del(&(THIS_MODULE->mkobj.kobj.entry));

  /*printk(KERN_ALERT "Begin first loop , %p\n", next);
  list_for_each(l, next) {
  	i++;
  }
  printk(KERN_ALERT "end first loop , %p\n", next);
  printk(KERN_ALERT "Next, %d\n", i);*/


  for ( i = 0 ; i < howmany ; i++ ) {
	printk(KERN_ALERT "Hello, %s\n", name);
  }
  return 0;
}

static void hello_exit(void)
{
  printk(KERN_ALERT "Goodbye, cruel %s\n", name);
}

module_init(hello_init);

module_exit(hello_exit);

