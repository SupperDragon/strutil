#include "common_util.h"
#include <ctype.h>
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

/*
 * 移除字符串左边的空白字符
*/
char* ltrim(char* str)
{
    char* lhs = str;
    char* rhs = str;

    if (empty_str(str)) {
        return str;
    }

    while(*rhs != '\0' && isblank(*rhs)) {
        ++rhs;
    }

    if (rhs != lhs) {
        while(*rhs != '\0') {
            *lhs++ = *rhs++;
        }
        *lhs='\0';
    }

    return str;
}

/*
 * 移除字符串右边的空白字符
*/
char* rtrim(char* str)
{
    char* rhs = NULL;

    if (empty_str(str)) {
        return str;
    }

    rhs = str + strlen(str) - 1;
    while (isblank(*rhs)) {
        *rhs-- = '\0';
    }
    return str;
}

/*
 * 移除字符串两端的空白字符
*/
char* trim(char* str)
{
    if (rtrim(str)) {
        return ltrim(str);
    }
    return str;
}
