#pragma once
#ifndef CHIP_RECTANGLE_HPP
#	define CHIP_RECTANGLE_HPP

#	include "shape.hpp"

class Rectangle : public Shape {
public:
	Rectangle(double a, double b); // Konstruktor

	void   setSize(double a, double b);
	double perimeter() const override;
	double area() const override;

private:
	double a{};
	double b{};
};

#endif