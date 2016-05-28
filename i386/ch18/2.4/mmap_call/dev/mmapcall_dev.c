#define MODULE
#include <linux/module.h>
#include <linux/kernel.h>      

#include <linux/fs.h>          
#include <linux/errno.h>       
#include <linux/types.h>       
#include <linux/fcntl.h>  
     
#include <linux/vmalloc.h>
#include <asm/uaccess.h>
#include <asm/io.h>

#include <asm/page.h>
#include <asm/mm.h>

#define   MMAPCALL_DEV_NAME            "mmapcall"
#define   MMAPCALL_DEV_MAJOR            240      

int mmapcall_open (struct inode *inode, struct file *filp)
{
    MOD_INC_USE_COUNT;
        
    return 0;
}

int mmapcall_release (struct inode *inode, struct file *filp)
{
    MOD_DEC_USE_COUNT;
    return 0;
}

int mmapcall_mmap(struct file *filp , struct vm_area_struct *vma ) 
{

    printk( "vm_pgoff     [%08X]\n", vma->vm_pgoff << PAGE_SHIFT );
    printk( "vm_start     [%08X]\n", vma->vm_start );
    printk( "vm_end       [%08X]\n", vma->vm_end );
    printk( "vm_flags     [%08X]\n", vma->vm_flags );
    
    return -EAGAIN;
}

struct file_operations mmapcall_fops =
{
    open     : mmapcall_open,
    release  : mmapcall_release,  
    mmap     : mmapcall_mmap,  
};

int init_module(void)
{
    int result;

    result = register_chrdev( MMAPCALL_DEV_MAJOR, MMAPCALL_DEV_NAME, &mmapcall_fops);
    if (result < 0) return result;

    return 0;
}

void cleanup_module(void)
{
    unregister_chrdev( MMAPCALL_DEV_MAJOR, MMAPCALL_DEV_NAME );
}

