#ifndef TOKEN_UTIL_H_
#define TOKEN_UTIL_H_
#ifdef __cplusplus
extern "C" {
#endif

/*
 * @brief: 根据指定的定界符(字符串)把字符串分割成一系列字段
 * @param[i] src: 要分割的字符串
 * @param[i] delim: 定界符,固定字符串
 * @param[o] dst: 指向分割好的字段的指针,指针指向的内存是动态分配的,需要用free()释放
 * @param[i] n: @dst数组的长度
 * @return: 成功则返回分割得到的字段数; 失败则返回-1
*/
int split_by_str(const char* src, const char* delim, char* dst[], int n);

/*
 * @brief: 根据指定的定界符(posix扩展正则表达式)把字符串分割成一系列字段
 * @param[i] src: 要分割的字符串
 * @param[i] delim: 定界符,支持perl正则表达式
 * @param[o] dst: 指向分割好的字段的指针,指针指向的内存是动态分配的,需要用free()释放
 * @param[i] n: @dst数组的长度
 * @return: 成功则返回分割得到的字段数; 失败则返回-1
*/
int split_by_reg(const char* src, const char* pattern, char* dst[], int n);

/*
 * @brief: 释放内存
 * @param[i/o]: 指向分割好的字段的指针数组,数组中指针指向的内存是动态分配的
 * @param[i] n: @dst数组的长度
*/
void free_tokens(char* tokens[], int n);

/*
 * @brief: 删除每个字段中的前缀与后缀空白字符
 * @param[i/o]: 指向分割好的字段的指针数组
 * @param[i] n: @dst数组的长度
*/
void trim_tokens(char* tokens[], int n);

#ifdef __cplusplus
}
#endif
#endif
