//
// Created by jacel on 4/13/2019.
//

#include "quad.h"

#include "button.h"
#include "graphics.h"
using namespace std;

/********** Quad *************/

Quad::Quad() {
    fill = {0, 0, 0};
    width = 50;
    height = 50;
}

Quad::Quad(color fill, point center, unsigned int width, unsigned int height) : Shape() {
	this->x = center.x;
	this->y = center.y;
	this->fill = fill;
    this->width = width;
    this->height = height;
}



unsigned int Quad::getWidth() const {
    return width;
}

unsigned int Quad::getHeight() const {
    return height;
}

void Quad::move(int deltaX, int deltaY) {
    x += deltaX;
    y += deltaY;
}

void Quad::resize(unsigned int width, unsigned int height) {
    this->width = width;
    this->height = height;
}

void Quad::draw() const {
	// set color and draw
    glColor3f(fill.red, fill.green, fill.blue);
    glBegin(GL_QUADS);
    glVertex2i(getLeftX(), getTopY());
    glVertex2i(getRightX(), getTopY());
    glVertex2i(getRightX(), getBottomY());
    glVertex2i(getLeftX(), getBottomY());
    glEnd();
}

std::ostream& Quad::doprint(std::ostream& out) const {
	out << "Quad centered at " << x << "," << y;
	return out;
}


// setters


void Quad::setColor(double red, double green, double blue) {
    fill = {red, green, blue};
}

void Quad::setColor(color fill) {
    this->fill = fill;
}



// getters

int Quad::getCenterX() const {
    return x;
}

int Quad::getLeftX() const {
    return x - (width / 2);
}

int Quad::getRightX() const {
    return x + (width / 2);
}

int Quad::getCenterY() const {
    return y;
}

int Quad::getTopY() const {
    return y - (height / 2);
}

int Quad::getBottomY() const {
    return y + (height / 2);
}

double Quad::getRed() const {
    return fill.red;
}

double Quad::getGreen() const {
    return fill.green;
}

double Quad::getBlue() const {
    return fill.blue;
}

color Quad::getFill() const {
    return fill;
}
