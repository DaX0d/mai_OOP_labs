#include <gtest/gtest.h>
#include <cmath>

#include "../include/rhomb.hpp"
#include "../include/pentagon.hpp"
#include "../include/hexagon.hpp"

const double EPS = 1e-6;

TEST(rhomb_tests, test_1) {
    std::vector<Point> points = {Point(0, 1), Point(1, 2), Point(2, 1), Point(1, 0)};
    Rhomb rhomb(points);
    std::cout << rhomb;
    ASSERT_EQ(rhomb.center(), Point(1, 1));
    ASSERT_EQ(static_cast<double>(rhomb), 2);
}

TEST(rhomb_tests, test_2) {
    std::vector<Point> points1 = {Point(0, 1), Point(1, 2), Point(2, 1), Point(1, 0)};
    std::vector<Point> points2 = {Point(3, 2.5), Point(4, 3.5), Point(5, 2.5), Point(4, 1.5)};
    ASSERT_EQ(Rhomb(points1), Rhomb(points2));
}

TEST(pentagon_tests, test_1) {
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

TEST(pentagon_tests, test_2) {
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

TEST(hexagon_tests, test_1) {
    const double R = 2;
    std::vector<Point> hexagon;
    for (int i = 0; i < 6; ++i) {
        double angle = 2 * M_PI * i / 6;
        hexagon.push_back(Point(R * std::cos(angle), R * std::sin(angle)));
    }
    Hexagon h(hexagon);
    std::cout << h;

    Point c = h.center();
    ASSERT_NEAR(c.x(), 0, EPS);
    ASSERT_NEAR(c.y(), 0, EPS);

    double area = static_cast<double>(h);
    double expected = 3 * std::sqrt(3) / 2 * R * R;
    ASSERT_NEAR(area, expected, EPS);
}

TEST(hexagon_tests, test_2) {
    const double R = 2;
    std::vector<Point> h1, h2;
    for (int i = 0; i < 6; ++i) {
        double angle = 2 * M_PI * i / 6;
        h1.push_back(Point(R * std::cos(angle) + 1, R * std::sin(angle) - 1));
    }
    for (int i = 0; i < 6; ++i) {
        double angle = 2 * M_PI * i / 6 + M_PI / 2;
        h2.push_back(Point(R * std::cos(angle) - 1, R * std::sin(angle) + 1));
    }
    ASSERT_EQ(Hexagon(h1), Hexagon(h2));
}

TEST(test_7, polymorphism_works) {
    std::vector<std::unique_ptr<Figure>> figures;

    std::vector<Point> r_points = {
        Point(0, 1), Point(1, 2), Point(2, 1), Point(1, 0)
    };
    figures.push_back(std::make_unique<Rhomb>(r_points));

    std::vector<Point> p_points;
    for (int i = 0; i < 5; ++i) {
        double angle = 2 * M_PI * i / 5;
        p_points.emplace_back(std::cos(angle), std::sin(angle));
    }
    figures.push_back(std::make_unique<Pentagon>(p_points));

    std::vector<Point> h_points;
    for (int i = 0; i < 6; ++i) {
        double angle = 2 * M_PI * i / 6;
        h_points.push_back(Point(std::cos(angle), std::sin(angle)));
    }
    figures.push_back(std::make_unique<Hexagon>(h_points));

    for (const auto& fig : figures) {
        Point c = fig->center();
        double area = static_cast<double>(*fig);

        ASSERT_TRUE(std::isfinite(c.x()));
        ASSERT_TRUE(std::isfinite(c.y()));
        ASSERT_GT(area, 0.0);
    }
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
