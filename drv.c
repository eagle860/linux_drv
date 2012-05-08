/* ��������drv.c */
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/device.h>

#define DRV_NAME         "drv"           // ������ cat /proc/devices
#define DRV_CLASS_NAME   "my_drv_class"  // udev�������������� ls /sys/class/
#define DRV_DEVICE_NAME  "my_drv_device" // udev�����������豸�� ls /dev/

static struct class *drv_class;
static struct device *drv_dev;
int major; // ���ڱ������豸��

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
    /* ע�������������豸��Ϊ0��ʾϵͳ�Զ��������豸�� */
    major = register_chrdev(0, DRV_NAME, &drv_fops);

    /* ������ʼ��ʱ����һ��DRV_CLASS������Ӧ���豸DRV_DEVICE*/
    drv_class = class_create(THIS_MODULE, DRV_CLASS_NAME);
    drv_dev = device_create(drv_class, NULL, MKDEV(major, 0), NULL, DRV_DEVICE_NAME);

    printk("drv_init\n");
    return 0;
}
static void drv_exit(void)
{
    /* �������豸��ж������ */
    unregister_chrdev(major, DRV_NAME); //ж������

    /* ���ٸ�class����Ӧ���豸 */
    device_unregister(drv_dev);
    class_destroy(drv_class);

    printk("drv_exit\n");
}
module_init(drv_init);
module_exit(drv_exit);

MODULE_AUTHOR("xxx");         // �������������
MODULE_DESCRIPTION("xxx");    // ���������������Ϣ
MODULE_LICENSE("GPL");        // ��ѭ��Э��
