#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static int __init init_hello(void)
{
	printk("Hello world.\n");

	return 0;
}

static void __exit cleanup_hello(void)
{
	printk("Goodbye world.\n");
}
module_init(init_hello);
module_exit(cleanup_hello);

MODULE_AUTHOR("Austin Kim <austindh.kim@gmail.com>");
MODULE_DESCRIPTION("Hello world");
MODULE_LICENSE("GPL");
