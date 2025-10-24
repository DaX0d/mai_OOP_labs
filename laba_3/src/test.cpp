#include <gtest/gtest.h>
#include <cmath>

#include "../include/rhomb.hpp"
#include "../include/pentagon.hpp"
#include "../include/hexagon.hpp"

const double EPS = 1e-6;

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

TEST(test_3, pentagon_tests) {
    const double R = 1.0;
    std::vector<Point> pentagon;
    for (int i = 0; i < 5; ++i) {
        double angle = 2 * M_PI * i / 5;
        pentagon.push_back(Point(R * std::cos(angle), R * std::sin(angle)));
    }
    Pentagon p(pentagon);
    std::cout << p;

    ASSERT_NEAR(p.center().x(), Point().x(), EPS);
    ASSERT_NEAR(p.center().y(), Point().y(), EPS);

    double area = static_cast<double>(p);
    double expected = 2.3776412907378841;
    ASSERT_NEAR(area, expected, 1e-6);
}

TEST(test_4, pentagon_tests) {
    std::vector<Point> p1, p2;

    const double R = 1.5;
    for (int i = 0; i < 5; ++i) {
        double angle = 2 * M_PI * i / 5;
        p1.push_back(Point(R * std::cos(angle), R * std::sin(angle)));
    }
    
    for (int i = 0; i < 5; ++i) {
        double angle = 2 * M_PI * i / 5;
        p2.push_back(Point(R * std::cos(angle) + 5, R * std::sin(angle) - 7));
    }
    
    ASSERT_EQ(Pentagon(p1), Pentagon(p2));
}


int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
