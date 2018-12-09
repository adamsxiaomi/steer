/********************************头文件****************************************/
#include <unistd.h>
#include <stdio.h>

#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "log.h"
/*******************************全局变量***************************************/
static int steer_fd;
/*********************************函数*****************************************/
/*
 *舵机转向
 *参数1:angle(in)    转向的角度
 *返回：0:转向成功，-1：失败
 */
int steer_turn(int angle)
{
    int ret;
    char buf;
    buf = angle & 0xff;
    ret = write(steer_fd, &buf, 1);
    if (ret <= 0) {
        print_err("steer turn failed\n");
        return -1;
    }

    return 0;
}

/*
 * 舵机初始化
 */
void steer_init(void)
{
    steer_fd = open("/dev/steer", O_RDWR);
    if (steer_fd < 0) {
        print_err("open /dev/steer failed!\n");
    }
}

/*
 * 舵机反初始化
 */
void steer_deinit(void)
{
    close(steer_fd);
}

