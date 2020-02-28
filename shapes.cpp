/*
 * shapes.cpp
 *
 * Parent class for circle and quad
 *
 * Written by Nicholas Hanoian on 04/12/2019.
 */




#include "shapes.h"

Shape::Shape() {
	x = 0;
	y = 0;
	fill = rgb(1,1,1);
	border = rgb(1,1,1);
}

int Shape::getX() const {
	return x;	
}

int Shape::getY() const {
	return y;
}

rgb Shape::getFill() const {
	return fill;
}

rgb Shape::getBorder() const {
	return border;
}

void Shape::setX(const int &x) {
	this->x = x;
}

void Shape::setY(const int &y) {
	this->y = y;
}

void Shape::setFill(const rgb &fill) {
	this->fill = fill;
}

void Shape::setBorder(const rgb &border) {
	this->border = border;
}

std::ostream& operator << (std::ostream& os, const Shape& sh) {
	return sh.doprint(os); // polymorphic print via reference
}
