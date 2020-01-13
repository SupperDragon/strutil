#ifndef COMMON_UTIL_H_
#define COMMON_UTIL_H_
#ifdef __cplusplus
extern "C" {
#endif
#include <stdbool.h>
#include <stddef.h>

/*
 * @brief: 判断一个字符串是否是空的
*/
bool empty_str(const char* str);

/*
 * @brief: 格式化字符串拼接
*/
int strfcat(char* dst, size_t size, const char* fmt, ...);

#ifdef __cplusplus
}
#endif
#endif
