/*
 *舵机驱动，使用pwm控制
 *周期20ms,占空比0.5~2.5ms = 0~180°
 */
/********************************头文件****************************************/
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/platform_device.h>
#include <linux/pwm.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
/********************************宏定义****************************************/
#define     DEFAULT_PERIOD  20000000
#define     DEFAULT_DUTY    19500000
/*****************************结构体和枚举*************************************/
/* steer设备控制结构体 */
struct steer_dev_ctrl {
    struct pwm_device *pwmdev;
    int major;
    struct cdev chardev;                /* 字符设备 */
    struct class *cls;            /* 字符设备类 */
};
/*******************************全局变量***************************************/
static struct steer_dev_ctrl *steer_ctl;
/*********************************函数*****************************************/
static ssize_t steer_write(struct file *file, const char __user *user_buf,
            size_t count, loff_t *ppos)
{
    int ret;
    char angle;
    int duty_ns;

    ret = copy_from_user(&angle, user_buf, 1);
    if (ret)
        return -EFAULT;

    duty_ns = DEFAULT_DUTY - ((2000000 * angle) / 180);
	ret = pwm_config(steer_ctl->pwmdev, duty_ns, DEFAULT_PERIOD);
	if (ret < 0) {
        pr_err("pwm config failed\n");
        return ret;
    }

    return 1;
}
static struct file_operations steer_fops = {
	.owner = THIS_MODULE,
    .write = steer_write,
};
static int steer_probe(struct platform_device *pdev)
{
	int ret;
	dev_t devid;
    int major;
	struct steer_dev_ctrl *p_ctl;

    p_ctl = devm_kzalloc(&pdev->dev, sizeof(struct steer_dev_ctrl), GFP_KERNEL);
    if (p_ctl == NULL) {
        dev_err(&pdev->dev, "steer_dev_ctrl has no memory to allocate\n");
        return -ENOMEM;
    }

    p_ctl->pwmdev = devm_pwm_get(&pdev->dev, NULL);
	if (IS_ERR(p_ctl->pwmdev)) {
        dev_err(&pdev->dev, "get pwm devcie failed\n");
        return PTR_ERR(p_ctl->pwmdev);
    }

	ret = pwm_config(p_ctl->pwmdev, 18500000, DEFAULT_PERIOD);
	if (ret < 0) {
        dev_err(&pdev->dev, "pwm config failed\n");
        return ret;
    }

    pwm_enable(p_ctl->pwmdev);

    alloc_chrdev_region(&devid, 0, 1, "steer");
    major = MAJOR(devid);
    p_ctl->major = major;
    cdev_init(&p_ctl->chardev, &steer_fops);
    cdev_add(&p_ctl->chardev, devid, 1);
    p_ctl->cls = class_create(THIS_MODULE, "steer");
    device_create(p_ctl->cls, NULL, MKDEV(major, 0), NULL, "steer"); /*/dev/steer*/

    steer_ctl = p_ctl;

    return 0;
}

static int steer_remove(struct platform_device *pdev)
{
    int major;

    major = steer_ctl->major;
    device_destroy(steer_ctl->cls, MKDEV(major, 0));
	class_destroy(steer_ctl->cls);
	cdev_del(&steer_ctl->chardev);
	unregister_chrdev_region(MKDEV(major, 0), 1);

	return 0;
}

static const struct of_device_id steer_pwm_dt_ids[] = {
	{ .compatible = "pwm-steer", },
	{ }
};

MODULE_DEVICE_TABLE(of, steer_pwm_dt_ids);

static struct platform_driver steer_pwm_driver = {
	.driver	= {
		.name		= "steer",
		.of_match_table	= of_match_ptr(steer_pwm_dt_ids),
	},
	.probe	= steer_probe,
	.remove	= steer_remove,
};

module_platform_driver(steer_pwm_driver);

MODULE_LICENSE("GPL");

