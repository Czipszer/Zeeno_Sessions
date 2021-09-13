#pragma once
#ifndef CHIP_CIRCLE_HPP
#	define CHIP_CIRCLE_HPP

#	include "shape.hpp"

class Circle : public Shape {
public:
	Circle(double r); // Konstruktor

	void   setSize(double r);
	double perimeter() const override;
	double area() const override;

private:
	double r{};
};

#endif