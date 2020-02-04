#ifndef COMMON_UTIL_H_
#define COMMON_UTIL_H_
#ifdef __cplusplus
extern "C" {
#endif
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

/*
 * @brief: 释放指针@ptr指向的动态内存,并将指针@ptr置为NULL
*/
#define FREE_PTR(ptr) if (ptr) {free(ptr); ptr = NULL;}

/*
 * @brief: 判断一个字符串是否是空的
*/
bool empty_str(const char* str);

/*
 * @brief: 格式化字符串拼接
*/
int strfcat(char* dst, size_t size, const char* fmt, ...);

/*
 * 移除字符串左边的空白字符
*/
char* ltrim(char* str);

/*
 * 移除字符串右边的空白字符
*/
char* rtrim(char* str);

/*
 * 移除字符串两端的空白字符
*/
char* trim(char* str);

#ifdef __cplusplus
}
#endif
#endif
