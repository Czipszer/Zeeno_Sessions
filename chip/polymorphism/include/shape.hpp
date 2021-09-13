#pragma once
#ifndef CHIP_SHAPE_HPP
#	define CHIP_SHAPE_HPP

class Shape {
public:
	virtual ~Shape() = default; // Virtualni destruktor

	virtual double perimeter() const = 0;
	virtual double area() const      = 0;
};

#endif