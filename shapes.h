/*
 * shapes.h
 *
 * Written by Nicholas Hanoian on 04/12/2019.
 */




#ifndef SHAPES_SHAPES_H
#define SHAPES_SHAPES_H

#include <iostream>

struct rgb {
	double red;
	double green;
	double blue;
	rgb(double red, double green, double blue) {
		this->red = red;
		this->green = green;
		this->blue = blue;
	}
	rgb() = default;
};

// =========================== Shape ===========================
class Shape {
protected:
	int x;
	int y;
	rgb fill;
	rgb border;
	
	// helper function to allow << operator to be overridden in derived classes
	virtual std::ostream& doprint(std::ostream&) const = 0;

public:
	Shape();

	// getters
	int getX() const;
	int getY() const;
	rgb getFill() const;
	rgb getBorder() const;

	// getters
	void setX(const int& x);
	void setY(const int& y);
	void setFill(const rgb &fill);
	void setBorder(const rgb &border);

	// pure virtual draw function to be implemented in child classes
	virtual void draw() const = 0;

	// calls doprint method of derived classes
    friend std::ostream& operator << (std::ostream& os, const Shape& sh);

	// polymorphic delete
	virtual ~Shape() {}
};


#endif //SHAPES_SHAPES_H
