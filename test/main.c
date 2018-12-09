/*
 * main.c
 */
/********************************头文件****************************************/
#include <stdio.h>
#include <stdlib.h>

#include "log.h"
#include "steer.h"
/*********************************函数*****************************************/
int main(int argc, char *argv[])
{
    int ret;
    int angle;

    if (argc != 2) {
        print_err("用法错误\n");
        goto err_usage;
    }

    steer_init();
    angle = atoi(argv[1]);

    if (angle < 0 || angle > 180) {
        print_err("转向角度不在范围内\n");
        goto err_usage;
    }
    ret = steer_turn(angle);
    if (ret) {
        print_err("转向失败\n");
        goto err_usage;
    }

    steer_deinit();
    return 0;

err_usage:
    print_info("用法:%s 转向角度[0~180°]\n", argv[0]);
    return -1;
}

