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

MODULE_DESCRIPTION("Module \"hello word\" pour noyau 2.6");
MODULE_AUTHOR("Julien Sopena, LIP6");
MODULE_LICENSE("GPL");

static int hello_init(void)
{
  printk(KERN_ALERT "Hello, world\n");
  return 0;
}

static void hello_exit(void)
{
  printk(KERN_ALERT "Goodbye, cruel world\n");
}

module_init(hello_init);

module_exit(hello_exit);

