#include "../token_util.h"
#include <gtest/gtest.h>
#define MAX_TOKEN 10

class token_test: public ::testing::Test {
public:
    token_test() {
        for (int i = 0; i < MAX_TOKEN; ++i) {
            m_dst[i] = NULL;
        }
    }
    ~token_test() {
        free_tokens(m_dst, MAX_TOKEN);
    }

    char* m_dst[MAX_TOKEN];
};

// split_by_str() 参数检查
TEST_F(token_test, split_by_str_check_param) {
    ASSERT_EQ(split_by_str(NULL, ":", m_dst, MAX_TOKEN), -1);
    ASSERT_EQ(split_by_str("", ":", m_dst, MAX_TOKEN), -1);
    ASSERT_EQ(split_by_str("FOO", ":", NULL, MAX_TOKEN), -1);
    ASSERT_EQ(split_by_str("FOO", ":", m_dst, 0), -1);
    ASSERT_EQ(split_by_str("FOO", ":", m_dst, -3), -1);
    ASSERT_EQ(split_by_str("FOO", NULL, m_dst, MAX_TOKEN), 1);
    ASSERT_STREQ(m_dst[0], "FOO");
}

// 当字符串中没有现在分隔符的时候, 直接把字符串作为一个字段
TEST_F(token_test, split_by_str_no_occurs) {
    ASSERT_EQ(split_by_str("FOO", ":", m_dst, MAX_TOKEN), 1);
    ASSERT_STREQ(m_dst[0], "FOO");
}

// 字符串中包含n个分隔符,根据分隔符将字符串分割为n+1个字段
TEST_F(token_test, split_by_str_occuus) {
    const char* src = "_reportmemoryexception:*:269:269:ReportMemoryException:"
                      "/var/db/reportmemoryexception:/usr/bin/false";
    const char* sep = ":";
    ASSERT_EQ(split_by_str(src, sep, m_dst, MAX_TOKEN), 7);
    ASSERT_STREQ(m_dst[0], "_reportmemoryexception");
    ASSERT_STREQ(m_dst[1], "*");
    ASSERT_STREQ(m_dst[2], "269");
    ASSERT_STREQ(m_dst[3], "269");
    ASSERT_STREQ(m_dst[4], "ReportMemoryException");
    ASSERT_STREQ(m_dst[5], "/var/db/reportmemoryexception");
    ASSERT_STREQ(m_dst[6], "/usr/bin/false");
}

// 支持空字段:
//  两个连续的分隔符表示一个空字段
//  行首为分隔符,也表示一个空字段
//  行尾为分隔符,也表示一个空字段
TEST_F(token_test, split_by_str_support_empty_token) {
    const char* src = ":_reportmemoryexception:*::269:";
    const char* sep = ":";
    ASSERT_EQ(split_by_str(src, sep, m_dst, MAX_TOKEN), 6);
    ASSERT_STREQ(m_dst[0], "");
    ASSERT_STREQ(m_dst[3], "");
    ASSERT_STREQ(m_dst[5], "");
}

// 支持多字符的分隔符
TEST_F(token_test, split_by_str_support_multi_char_delim) {
    const char* src = "**_reportmemory**exception****269**";
    const char* sep = "**";
    ASSERT_EQ(split_by_str(src, sep, m_dst, MAX_TOKEN), 6);
    ASSERT_STREQ(m_dst[0], "");
    ASSERT_STREQ(m_dst[1], "_reportmemory");
    ASSERT_STREQ(m_dst[2], "exception");
    ASSERT_STREQ(m_dst[3], "");
    ASSERT_STREQ(m_dst[4], "269");
    ASSERT_STREQ(m_dst[5], "");
}

// split_by_reg() 参数检查
TEST_F(token_test, split_by_reg_check_param) {
    ASSERT_EQ(split_by_reg(NULL, ":*", m_dst, MAX_TOKEN), -1);
    ASSERT_EQ(split_by_reg("", ":*", m_dst, MAX_TOKEN), -1);
    ASSERT_EQ(split_by_reg("FOO", ":*", NULL, MAX_TOKEN), -1);
    ASSERT_EQ(split_by_reg("FOO", ":*", m_dst, 0), -1);
    ASSERT_EQ(split_by_reg("FOO", ":*", m_dst, -3), -1);
    ASSERT_EQ(split_by_reg("FOO", NULL, m_dst, MAX_TOKEN), 1);
    ASSERT_STREQ(m_dst[0], "FOO");
}

// 当字符串中没有现在分隔符的时候, 直接把字符串作为一个字段
TEST_F(token_test, split_by_reg_no_occurs) {
    ASSERT_EQ(split_by_reg("FOO", ":{2}", m_dst, MAX_TOKEN), 1);
    ASSERT_STREQ(m_dst[0], "FOO");
}

// 字符串中包含n个分隔符,根据分隔符将字符串分割为n+1个字段
TEST_F(token_test, split_by_reg_occuus) {
    const char* src = "_reportmemoryexception * 269\t269\t"
                      "ReportMemoryException "
                      "/var/db/reportmemoryexception\t/usr/bin/false";
    const char* pat = "[[:blank:]]{1}";
    ASSERT_EQ(split_by_reg(src, pat, m_dst, MAX_TOKEN), 7);
    ASSERT_STREQ(m_dst[0], "_reportmemoryexception");
    ASSERT_STREQ(m_dst[1], "*");
    ASSERT_STREQ(m_dst[2], "269");
    ASSERT_STREQ(m_dst[3], "269");
    ASSERT_STREQ(m_dst[4], "ReportMemoryException");
    ASSERT_STREQ(m_dst[5], "/var/db/reportmemoryexception");
    ASSERT_STREQ(m_dst[6], "/usr/bin/false");
}

// 支持空字段:
//  两个连续的分隔符表示一个空字段
//  行首为分隔符,也表示一个空字段
//  行尾为分隔符,也表示一个空字段
TEST_F(token_test, split_by_reg_support_empty_token) {
    const char* src = "::_reportmemoryexception::*::::269::";
    const char* pat = ":{2}";
    ASSERT_EQ(split_by_reg(src, pat, m_dst, MAX_TOKEN), 6);
    ASSERT_STREQ(m_dst[0], "");
    ASSERT_STREQ(m_dst[3], "");
    ASSERT_STREQ(m_dst[5], "");
}

TEST_F(token_test, trim_tokens) {
    m_dst[0] = strdup("hello");
    m_dst[1] = strdup("	  hello");
    m_dst[2] = strdup("hello  		");
    m_dst[3] = strdup("		  hello  		");
	trim_tokens(m_dst, 4);
	ASSERT_STREQ(m_dst[0], "hello");
	ASSERT_STREQ(m_dst[1], "hello");
	ASSERT_STREQ(m_dst[2], "hello");
	ASSERT_STREQ(m_dst[3], "hello");
}
