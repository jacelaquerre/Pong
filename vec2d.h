/*
 * vec2d.h
 *
 * class to store a 2-dimensional vector. Used for storing and
 * manipulating ball velocity in the pong game.
 *
 * Written by Nicholas Hanoian on 04/17/2019.
 */




#ifndef VEC2D_H
#define VEC2D_H

#include <map>

class Vec2d {
private:
	double x, y;
public:
	// default constructor
	Vec2d();
	// constructor {x,y}
	Vec2d(std::pair<double, double> p);

	// add another vector to this one
	friend Vec2d operator +(const Vec2d& v1, const Vec2d& v2);
	// multiply this vector by another (i.e. v1.x * v2.x, v1.y * v2.y)
	friend Vec2d operator *(const Vec2d& v1, const Vec2d& v2);

	Vec2d& operator *=(const Vec2d& v);

	// multiply magnitude by a scaling factor, keeping same angle
	void multiplyMagnitude(double factor);
	
	// setters
	// set x and y explicitly
	void set(Vec2d v);
	// set the angle, keeping the same magnitude
	void setAngle(double angle);
	// set the magnitude, keeping the same angle
	void setMagnitude(double magnitude);
	// set angle and magnitude explicitly
	void setBoth(double angle, double magnitude);

	// getters
	double getX() const;
	double getY() const;
	double getAngle() const;
	double getMagnitude() const;
};




#endif
