#include <cmath>
#include <iostream>
#include <numbers>

#include "circle.hpp"

Circle::Circle(double r) {
	setSize(r);
}

void Circle::setSize(double rx) {
	r = rx;
}

double Circle::perimeter() const {
	return (2 * std::numbers::pi * r);
}

double Circle::area() const {
	return (std::numbers::pi * std::pow(r, 2));
}