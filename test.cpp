#include <gtest/gtest.h>
#include "find_num.h"

TEST(test_1, basic_test_set) {
    ASSERT_TRUE(find_num("qw34ert67yui8") == 34678);
}

TEST(test_2, basic_test_set) {
    ASSERT_TRUE(find_num("dsjhfg123456hdf90") == 12345690);
}

TEST(test_3, basic_test_set) {
    ASSERT_TRUE(find_num("a") == 0);
}

TEST(test_4, basic_test_set) {
    ASSERT_TRUE(find_num("1234567890dsfhgwdhf162547") == 1234567890162547);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
