#include <gtest/gtest.h>
#include <cmath>

#include "../include/square.hpp"
#include "../include/rectangle.hpp"
#include "../include/trapez.hpp"

const double EPS = 1e-6;

//================== SQUARE TESTS ==================//

TEST(square_tests, center_and_area) {
    // square 2x2 with center at (1,1)
    std::vector<Point<double>> pts = {
        {0,0}, {2,0}, {2,2}, {0,2}
    };

    Square<double> sq(pts);

    Point<double> c = sq.center();
    ASSERT_NEAR(c.x(), 1.0, EPS);
    ASSERT_NEAR(c.y(), 1.0, EPS);

    double area = static_cast<double>(sq);
    ASSERT_NEAR(area, 4.0, EPS); // 2x2
}

TEST(square_tests, equality) {
    std::vector<Point<double>> p1 = {
        {0,0}, {2,0}, {2,2}, {0,2}
    };
    std::vector<Point<double>> p2 = {
        {5,5}, {7,5}, {7,7}, {5,7}
    };

    ASSERT_EQ(Square<double>(p1), Square<double>(p2)); // same area
}

//================== RECTANGLE TESTS ==================//

TEST(rectangle_tests, center_and_area) {
    std::vector<Point<double>> pts = {
        {0,0}, {3,0}, {3,2}, {0,2}
    };

    Rectangle<double> r(pts);

    Point<double> c = r.center();
    ASSERT_NEAR(c.x(), 1.5, EPS);
    ASSERT_NEAR(c.y(), 1.0, EPS);

    double area = static_cast<double>(r);
    ASSERT_NEAR(area, 6.0, EPS);
}

TEST(rectangle_tests, equality) {
    std::vector<Point<double>> p1 = {
        {0,0}, {4,0}, {4,1}, {0,1}
    };
    std::vector<Point<double>> p2 = {
        {10,10}, {14,10}, {14,11}, {10,11}
    };

    ASSERT_EQ(Rectangle<double>(p1), Rectangle<double>(p2));
}

//================== TRAPEZOID TESTS ==================//

TEST(trapezoid_tests, center_and_area) {
    // trapezoid with bases 4 and 2, height 2
    std::vector<Point<double>> pts = {
        {0,0}, {4,0}, {3,2}, {1,2}
    };

    Trapezoid<double> tr(pts);

    Point<double> c = tr.center(); 
    ASSERT_TRUE(std::isfinite(c.x()));
    ASSERT_TRUE(std::isfinite(c.y()));

    double area = static_cast<double>(tr);
    double expected = (4 + 2) * 0.5 * 2; // (b1+b2)/2 * h = 6
    ASSERT_NEAR(area, expected, EPS);
}

TEST(trapezoid_tests, equality) {
    std::vector<Point<double>> p1 = {
        {0,0}, {4,0}, {3,2}, {1,2}
    };
    std::vector<Point<double>> p2 = {
        {10,5}, {14,5}, {13,7}, {11,7}
    };

    ASSERT_EQ(Trapezoid<double>(p1), Trapezoid<double>(p2));
}

//================== POLYMORPHISM TEST ==================//

TEST(polymorphism_test, using_smart_pointers) {
    std::vector<std::unique_ptr<Figure<double>>> figs;

    figs.push_back(std::make_unique<Square<double>>(
        std::vector<Point<double>>{{0,0},{2,0},{2,2},{0,2}}
    ));

    figs.push_back(std::make_unique<Rectangle<double>>(
        std::vector<Point<double>>{{0,0},{3,0},{3,2},{0,2}}
    ));

    figs.push_back(std::make_unique<Trapezoid<double>>(
        std::vector<Point<double>>{{0,0},{4,0},{3,2},{1,2}}
    ));

    for (auto &fig : figs) {
        Point<double> c = fig->center();
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
