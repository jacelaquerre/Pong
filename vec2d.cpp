#include "vec2d.h"
#define _USE_MATH_DEFINES
#include <math.h>

Vec2d::Vec2d() {
	x = 0;
	y = 0;
}

Vec2d::Vec2d(std::pair<double, double> p) {
	x = p.first;
	y = p.second;
}

Vec2d  operator +(const Vec2d& lhs, const Vec2d& rhs) {
	double x = lhs.getX() + rhs.getX();
	double y = lhs.getY() + rhs.getY();
	return Vec2d({x, y});
}

Vec2d  operator *(const Vec2d& lhs, const Vec2d& rhs) {
	double x = lhs.getX() * rhs.getX();
	double y = lhs.getY() * rhs.getY();
	return Vec2d({x, y});
}

Vec2d& Vec2d::operator*=(const Vec2d& rhs) {
	x *= rhs.getX();
	y *= rhs.getY();
	return *this;
}

void Vec2d::multiplyMagnitude(double factor) {
	setMagnitude(getMagnitude() * factor);
}

void Vec2d::set(Vec2d v) {
	x = v.x;
	y = v.y;
}

void Vec2d::setAngle(double angle) {
	double magnitude = getMagnitude();
	setBoth(angle, magnitude);
		
}
	
void Vec2d::setMagnitude(double magnitude) {
	double angle = getAngle();
	if (x < 0) {
		angle += M_PI;
	}
	setBoth(angle, magnitude);
}
	
void Vec2d::setBoth(double angle, double magnitude) {
	x = magnitude * cos(angle);
	y = magnitude * (- sin(angle)); // negative sin since down y is increasing
}

double Vec2d::getAngle() const {
	return atan(y/x);
}

double Vec2d::getX() const {
	return x;
}

double Vec2d::getY() const {
	return y;
}

double Vec2d::getMagnitude() const {
	return sqrt(x * x + y * y);
}
