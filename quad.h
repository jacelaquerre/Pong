//
// Created by jacel on 4/13/2019.
//

#ifndef PONG_QUAD_H
#define PONG_QUAD_H

#include <string>
#include <functional>
#include "shapes.h"

// struct for storing rgb values (0--1 range for each color)
struct color {
    double red;
    double green;
    double blue;
};

// struct for storing an ordered pair
struct point {
    int x;
    int y;
};

class Quad : public Shape {
private:
    color fill;
    unsigned int width;
    unsigned int height;

public:
    Quad();
    Quad(color fill, point center, unsigned int width, unsigned int height);

	// position getters
    int getCenterX() const;
    int getLeftX() const;
    int getRightX() const;
    int getCenterY() const;
    int getTopY() const;
    int getBottomY() const;

	// color getters
    double getRed() const;
    double getGreen() const;
    double getBlue() const;
    color getFill() const;

	// size getters
    unsigned int getWidth() const;
    unsigned int getHeight() const;

	// setters
    void setColor(double red, double green, double blue);
    void setColor(color fill);

	// modifiers
	// move position by deltaX and deltaY
	void move(int deltaX, int deltaY);

	// change size to width and height
    void resize(unsigned int width, unsigned int height);

	// other functions
    void draw() const override;
	std::ostream& doprint(std::ostream& out) const override;

};


#endif //PONG_QUAD_H
