#include <cmath>
#include <iostream>

#include "rectangle.hpp"

Rectangle::Rectangle(double a, double b) {
	setSize(a, b);
}

void Rectangle::setSize(double ax, double bx) {
	a = ax;
	b = bx;
}

double Rectangle::perimeter() const {
	return (2 * (a + b));
}

double Rectangle::area() const {
	return (a * b);
}