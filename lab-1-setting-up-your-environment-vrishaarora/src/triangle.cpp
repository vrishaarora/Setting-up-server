#include "../header/triangle.hpp"

void Triangle::t_set_base(int b) {
    this->base = b;
}

void Triangle::t_set_height(int t) {
    this->height = t;
}

double Triangle::t_area() {
    return this->base * this->height * 0.5 ;
}