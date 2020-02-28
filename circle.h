//
// Created by jacel on 4/6/2019.
//

#ifndef GRAPHICS_STARTER_CIRCLE_H
#define GRAPHICS_STARTER_CIRCLE_H

#include "shapes.h"
#include <iostream>
#include "graphics.h"
#include "vec2d.h"

class Circle : public Shape {

private:
	int radius;
		
public:
	// constructors
	Circle();
	Circle(int radius);
	Circle(int x, int y, int radius);

	// getters
	int getRadius() const;

	int getLeftX() const;
	int getRightX() const;
	int getTopY() const;
	int getBottomY() const;
	int getCenterY() const;

	
	// must be >= 0
	void setRadius(int radius);

	virtual void draw() const override;

	// for overriding << operator
	std::ostream& doprint(std::ostream& out) const override;
};



#endif //GRAPHICS_STARTER_CIRCLE_H
