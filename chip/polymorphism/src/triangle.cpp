#include <cmath>
#include <iostream>

#include "triangle.hpp"

Triangle::Triangle(double a, double b, double c) {
	setSize(a, b, c);
}
Triangle::Triangle() {
}

void Triangle::setSize(double ax, double bx, double cx) {
	a  = ax;
	b  = bx;
	c  = cx;
	va = c * sin(b / c);
}

double Triangle::perimeter() const {
	return (a + b + c);
}

double Triangle::area() const {
	return (0.5 * a * va);
}