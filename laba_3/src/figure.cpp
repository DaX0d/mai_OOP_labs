#include "../include/figure.hpp"

Figure::Figure(std::vector<Point>& points) {
    __points = points;
}

Figure::Figure(Figure&& fig) {

}