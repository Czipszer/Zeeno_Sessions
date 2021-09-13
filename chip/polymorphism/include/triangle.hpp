#pragma once
#ifndef CHIP_TRIANGLE_HPP
#	define CHIP_TRIANGLE_HPP

#	include "shape.hpp"

class Triangle : public Shape {
public:
	Triangle();                             // Konstruktor
	Triangle(double a, double b, double c); // Konstruktor

	void   setSize(double a, double b, double c);
	double perimeter() const override;
	double area() const override;

private:
	double a{};
	double b{};
	double c{};
	double va{};
};

#endif