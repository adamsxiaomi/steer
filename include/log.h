/*
 */
#ifndef __STORAGE_H
#define __STORAGE_H
/********************************头文件****************************************/
#include <stdio.h>
/*********************************枚举*****************************************/
enum log_level {
    LOG_LEVEL_DISABLE = 0,
    LOG_LEVEL_ERR,
    LOG_LEVEL_WARN,
    LOG_LEVEL_INFO
};
/********************************宏定义****************************************/
#define LOG_NONE          "\033[m"
#define LOG_RED           "\033[0;32;31m"
#define LOG_GREEN         "\033[0;32;32m"
#define LOG_BLUE          "\033[0;32;34m"
#define LOG_DARY_GRAY     "\033[1;30m"
#define LOG_CYAN          "\033[0;36m"
#define LOG_PURPLE        "\033[0;35m"
#define LOG_BROWN         "\033[0;33m"
#define LOG_YELLOW        "\033[1;33m"
#define LOG_WHITE         "\033[1;37m"

#define LOG_ERROR_PRE_STR       LOG_RED "[error]: "
#define LOG_WARN_PRE_STR        LOG_YELLOW "[warn]: "
#define LOG_INFO_PRE_STR        LOG_GREEN "[info]: "

#define LOG_PRINT               printf

/*
 *功能：log日志错误打印
 *参数：与printf参数一致
 */
#define print_err(fmt, ...)                                 \
        do {                                                \
            if (log_get_level() >= LOG_LEVEL_ERR) {         \
                LOG_PRINT(LOG_ERROR_PRE_STR                 \
                    "\'%s\':%d: " fmt LOG_NONE,             \
                    __FUNCTION__, __LINE__, ##__VA_ARGS__); \
            }                                               \
        } while (0)

/*
 *功能：log日志警告打印
 *参数：与printf参数一致
 */
#define print_warn(fmt, ...)                                \
        do {                                                \
            if (log_get_level() >= LOG_LEVEL_WARN) {        \
                LOG_PRINT(LOG_WARN_PRE_STR                  \
                    "\'%s\':%d: " fmt LOG_NONE,             \
                    __FUNCTION__, __LINE__, ##__VA_ARGS__); \
            }                                               \
        } while (0)

/*
 *功能：log日志消息打印
 *参数：与printf参数一致
 */
#define print_info(fmt, ...)                                \
        do {                                                \
            if (log_get_level() >= LOG_LEVEL_INFO) {        \
                LOG_PRINT(LOG_INFO_PRE_STR                  \
                    "\'%s\':%d: " fmt LOG_NONE,             \
                    __FUNCTION__, __LINE__, ##__VA_ARGS__); \
            }                                               \
        } while (0)

/*
 *功能：log日志原生错误打印
 *参数：与printf参数一致
 */
#define print_err_raw(fmt, ...)                                 \
        do {                                                    \
            if (log_get_level() >= LOG_LEVEL_ERR) {             \
                LOG_PRINT(LOG_RED fmt LOG_NONE, ##__VA_ARGS__); \
            }                                                   \
        } while (0)

/*
 *功能：log日志原生消息打印
 *参数：与printf参数一致
 */
#define print_warn_raw(fmt, ...)                                   \
        do {                                                       \
            if (log_get_level() >= LOG_LEVEL_WARN) {               \
                LOG_PRINT(LOG_YELLOW fmt LOG_NONE, ##__VA_ARGS__); \
            }                                                      \
        } while (0)

/*
 *功能：log日志原生消息打印
 *参数：与printf参数一致
 */
#define print_info_raw(fmt, ...)                                  \
        do {                                                      \
            if (log_get_level() >= LOG_LEVEL_INFO) {              \
                LOG_PRINT(LOG_GREEN fmt LOG_NONE, ##__VA_ARGS__); \
            }                                                     \
        } while (0)

/*********************************函数*****************************************/
/*
 *功能：设置log日志输出等级
 *参数1：lev：log输出等级值，值在enum log_level中定义
 *返回：无
 */
void log_set_level(enum log_level lev);

/*
 *功能：获取log日志输出等级
 *参数1：lev：log输出等级值，值在enum log_level中定义
 *返回：无
 */
int log_get_level(void);


#endif /* __STORAGE_H */
