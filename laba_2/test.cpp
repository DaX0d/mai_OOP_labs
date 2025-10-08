#include <gtest/gtest.h>
#include "thirteen.h"

TEST(test_1, basic_test_set) {
    ASSERT_EQ(Thirteen(13).get_as_string(), std::string("10"));
    std::vector<unsigned char> th = Thirteen("123").get_as_array();
    ASSERT_EQ(th[0], '3'); ASSERT_EQ(th[1], '2'); ASSERT_EQ(th[2], '1');
}

TEST(test_2, basic_test_set) {
    ASSERT_TRUE(Thirteen("13").more(Thirteen(13)));
    ASSERT_FALSE(Thirteen(13).more(Thirteen(13)));
    ASSERT_TRUE(Thirteen().eq(Thirteen("0")));
    ASSERT_TRUE(Thirteen(7).less(Thirteen(8)));
    ASSERT_TRUE(Thirteen("C").eq(Thirteen(12)));
}

TEST(test_3, basic_test_set) {
    ASSERT_EQ((Thirteen(5).plus(Thirteen(10))).get_as_array(), Thirteen(15).get_as_array());
    ASSERT_EQ((Thirteen(13).minus(Thirteen("10"))).get_as_int10(), 0);
}

TEST(test_4, basic_test_set) {
    Thirteen one(1);
    one.pluseq(Thirteen(10));
    ASSERT_EQ(one.get_as_string(), "B");
    one.minuseq(Thirteen("B"));
    ASSERT_TRUE(one.eq(Thirteen()));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
