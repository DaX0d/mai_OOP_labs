#include <gtest/gtest.h>

#include "../include/rhomb.hpp"
#include "../include/pentagon.hpp"
#include "../include/hexagon.hpp"


TEST(test_1, rhomb_tests) {
    std::vector<Point> points = {Point(0, 1), Point(1, 2), Point(2, 1), Point(1, 0)};
    Rhomb rhomb(points);
    std::cout << rhomb;
    ASSERT_EQ(rhomb.center(), Point(1, 1));
    ASSERT_EQ(static_cast<double>(rhomb), 2);
}

TEST(test_2, rhomb_tests) {
    std::vector<Point> points1 = {Point(0, 1), Point(1, 2), Point(2, 1), Point(1, 0)};
    std::vector<Point> points2 = {Point(3, 2.5), Point(4, 3.5), Point(5, 2.5), Point(4, 1.5)};
    ASSERT_EQ(Rhomb(points1), Rhomb(points2));
}


int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
