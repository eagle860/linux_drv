/* 驱动程序drv.c */
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/device.h>

#define DRV_NAME         "drv"           // 驱动名 cat /proc/devices
#define DRV_CLASS_NAME   "my_drv_class"  // udev创建的驱动类名 ls /sys/class/
#define DRV_DEVICE_NAME  "my_drv_device" // udev创建的驱动设备名 ls /dev/

static struct class *drv_class;
static struct device *drv_dev;
int major; // 用于保存主设备号

static int drv_open(struct inode *inode, struct file *file)
{
    printk("drv_open\n");
    return 0;
}
static ssize_t drv_read(struct file *filp, char __user *buff, size_t count, loff_t *offp)
{
    printk("drv_read \n");
    return 0;
}
static struct file_operations drv_fops = {
    .owner = THIS_MODULE,
    .open = drv_open,
    .read = drv_read,
};
static int drv_init(void)
{
    /* 注册驱动程序，主设备号为0表示系统自动分配主设备号 */
    major = register_chrdev(0, DRV_NAME, &drv_fops);

    /* 驱动初始化时创建一个DRV_CLASS，及对应的设备DRV_DEVICE*/
    drv_class = class_create(THIS_MODULE, DRV_CLASS_NAME);
    drv_dev = device_create(drv_class, NULL, MKDEV(major, 0), NULL, DRV_DEVICE_NAME);

    printk("drv_init\n");
    return 0;
}
static void drv_exit(void)
{
    /* 根据主设备号卸载驱动 */
    unregister_chrdev(major, DRV_NAME); //卸载驱动

    /* 销毁该class及对应的设备 */
    device_unregister(drv_dev);
    class_destroy(drv_class);

    printk("drv_exit\n");
}
module_init(drv_init);
module_exit(drv_exit);

MODULE_AUTHOR("xxx");         // 驱动程序的作者
MODULE_DESCRIPTION("xxx");    // 驱动程序的描述信息
MODULE_LICENSE("GPL");        // 遵循的协议
