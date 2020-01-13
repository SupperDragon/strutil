#include "common_util.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

/*
 * @brief: 判断一个字符串是否是空的
*/
bool empty_str(const char* str)
{
    if (str == NULL) {
        return true;
    }
    return *str == '\0';
}

/*
 * @brief: 格式化字符串拼接
*/
int strfcat(char* dst, size_t size, const char* fmt, ...)
{
    int ret = 0;
    va_list args;
    size_t curr_sz = 0;

    if (!dst || !fmt) {
        return -1;
    }
    
    if ((curr_sz = strnlen(dst, size)) >= size) {
        return 0;
    }

    va_start(args, fmt);
    ret = vsnprintf(dst + curr_sz, size - curr_sz, fmt, args);
    va_end(args);

    return ret;
}
