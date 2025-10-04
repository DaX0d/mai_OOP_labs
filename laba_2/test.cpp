#include <gtest/gtest.h>
#include "thirteen.h"

TEST(test_1, basic_test_set) {
    ASSERT_EQ(Thirteen(13).get_as_string(), std::string("10"));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
