#include <gtest/gtest.h>
#include "thirteen.h"

TEST(test_1, basic_test_set) {
    ASSERT_EQ(Thirteen(13).get_as_string(), std::string("10"));
    std::vector<unsigned char> th = Thirteen("123").get_as_array();
    ASSERT_EQ(th[0], '3'); ASSERT_EQ(th[1], '2'); ASSERT_EQ(th[2], '1');
}

TEST(test_2, basic_test_set) {
    ASSERT_TRUE(Thirteen("13") > Thirteen(13));
    ASSERT_FALSE(Thirteen(13) > Thirteen(13));
    ASSERT_TRUE(Thirteen() == Thirteen("0"));
    ASSERT_TRUE(Thirteen(7) < Thirteen(8));
    ASSERT_TRUE(Thirteen("C") == Thirteen(12));
}

TEST(test_3, basic_test_set) {
    ASSERT_EQ((Thirteen(5) + Thirteen(10)).get_as_array(), Thirteen(15).get_as_array());
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
