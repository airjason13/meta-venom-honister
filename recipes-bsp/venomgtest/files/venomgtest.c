#include <linux/kernel.h>		/* We're doing kernel work */
#include <linux/module.h>		/* Specifically, a module */
#include <linux/proc_fs.h>		/* Necessary because we use the proc fs */
#include <linux/uaccess.h>		/* for copy_from_user */
#include <linux/version.h>

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 6, 0)
#define HAVE_PROC_OPS
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(3, 10, 0)
#define HAVE_PROC_READ_SUITE
#endif

MODULE_LICENSE("Dual BSD/GPL");

#define PROCFS_MAX_SIZE			1024
#define PROCFS_NAME			"venom" 

struct proc_dir_entry *venom=NULL;

int hello_val=0;

/* The buffer used to store character for this module */
static char procfs_buffer[PROCFS_MAX_SIZE];
/* The size of the buffer */
static ssize_t procfs_buffer_size = 0;
 
static ssize_t venomproc_read(struct file *file, char __user *buff,
                             size_t buffer_len, loff_t *off)
{

	int plen = procfs_buffer_size;
    	ssize_t ret = plen;
    	if (*off >= plen || copy_to_user(buff, procfs_buffer, plen)) {
        	pr_info("copy_to_user failed\n");
        	ret = 0;
    	} else {
        	pr_info("procfile read %s\n", file->f_path.dentry->d_name.name);
        	*off += plen;
    	}
    	return ret;
}

 
static ssize_t venomproc_write(struct file *file, const char __user *buff,
                              size_t len, loff_t *off)
{
#if 1
	procfs_buffer_size = len;
    	if (procfs_buffer_size > PROCFS_MAX_SIZE)
        	procfs_buffer_size = PROCFS_MAX_SIZE;

	if (copy_from_user(procfs_buffer, buff, procfs_buffer_size)) {
		pr_info("copy_from_user failed\n");
        	return -EFAULT;
	}

	/* supports only max to 1023 bytes string */
	procfs_buffer[procfs_buffer_size & (PROCFS_MAX_SIZE - 1)] = '\0';
    	pr_info("procfile write %s\n", procfs_buffer);

    	return procfs_buffer_size;
#endif
}

 
#ifdef HAVE_PROC_OPS
static const struct proc_ops proc_file_fops = {
    .proc_read = venomproc_read,
    .proc_write = venomproc_write,
};
#else
static const struct file_operations proc_file_fops = {
    .read = venom_proc_read,
    .write = venom_proc_write,
};
#endif
 

 

static int __init_venom(void){
	//venom = create_proc_entry("venom", 0, NULL);
	venom = proc_create(PROCFS_NAME, 0644, NULL, &proc_file_fops);
	if (NULL == venom) {
#ifdef HAVE_PROC_READ_SUITE
		remove_proc_entry(PROCFS_NAME, NULL);
#else
        	proc_remove(venom);
#endif
        	pr_alert("Error:Could not initialize /proc/%s\n", PROCFS_NAME);
        	return -ENOMEM;
	}               
	return 0;

}

 

static void __exit_venom(void){
#ifdef HAVE_PROC_READ_SUITE
	remove_proc_entry(PROCFS_NAME, NULL);
#else
        proc_remove(venom);
#endif
    	pr_info("/proc/%s removed\n", PROCFS_NAME);
}

 

module_init(__init_venom);

module_exit(__exit_venom);


