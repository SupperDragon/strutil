#include "../common_util.h"
#include <gtest/gtest.h>

class test_empty_str: public ::testing::Test {
public:
    test_empty_str(): m_test("Hello, World") {
        // TODO
    }
    ~test_empty_str() {
        // TODO
    }
    const char* m_test;
};

TEST_F(test_empty_str, return_true_if_null) {
    ASSERT_TRUE(empty_str(NULL));
    ASSERT_FALSE(empty_str(m_test));
}

TEST_F(test_empty_str, return_true_if_empty) {
    ASSERT_TRUE(empty_str(""));
    ASSERT_FALSE(empty_str(m_test));
}

class test_strfcat: public ::testing::Test {
public:
    test_strfcat(): max_buff_sz(1024), buff(NULL) {
        buff = (char*)calloc(1, max_buff_sz);
    }
    ~test_strfcat() {
        if (buff) {
            free(buff);
        }
    }

    const size_t max_buff_sz;
    char* buff;
};

TEST_F(test_strfcat, check_valid_args) {
    ASSERT_EQ(strfcat(NULL, 100, "%s"), -1);
    ASSERT_EQ(strfcat(buff, 100, NULL), -1);
}

TEST_F(test_strfcat, append_none_fmt_str) {
    ASSERT_EQ(strfcat(buff, max_buff_sz, "Hello"), strlen("Hello"));
    ASSERT_STREQ(buff, "Hello");

    ASSERT_EQ(strfcat(buff, max_buff_sz, "World"), strlen("World"));
    ASSERT_STREQ(buff, "HelloWorld");
}

TEST_F(test_strfcat, append_fmt_str) {
    ASSERT_EQ(strfcat(buff, max_buff_sz, "%s%s", "Hello", "World"), strlen("HelloWorld"));
    ASSERT_STREQ(buff, "HelloWorld");
}

TEST_F(test_strfcat, limit_total_size) {
    strfcat(buff, 10, "%s%s%s", "Hello", ", ", "World");
    ASSERT_EQ(strlen(buff), 9);
    ASSERT_STREQ(buff, "Hello, Wo");
}

class test_trim_str: public ::testing::Test {
public:
    test_trim_str() {
        strcpy(m_demo, "		  demo  		");
    }
    ~test_trim_str() {

    }
    char m_demo[1024];
};

TEST_F(test_trim_str, ltrim) {
    char empty[1] = {'\0'};
    ASSERT_EQ(ltrim(NULL), nullptr);
    ASSERT_STREQ(ltrim(empty), "");
    ASSERT_STREQ(ltrim(m_demo), "demo  		");
}

TEST_F(test_trim_str, rtrim) {
    char empty[1] = {'\0'};
    ASSERT_EQ(rtrim(NULL), nullptr);
    ASSERT_STREQ(rtrim(empty), "");
    ASSERT_STREQ(rtrim(m_demo), "		  demo");
}

TEST_F(test_trim_str, trim) {
    char empty[1] = {'\0'};
    ASSERT_EQ(trim(NULL), nullptr);
    ASSERT_STREQ(trim(empty), "");
    ASSERT_STREQ(trim(m_demo), "demo"); 
}
