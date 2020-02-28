/*
 * confetti.h
 *
 * For showing falling confetti on the screen when the user wins
 *
 * Written by Nicholas Hanoian on 04/16/2019.
 */


#ifndef CONFETTI_H
#define CONFETTI_H

#include "quad.h"
#include "shapes.h"
#include <vector>
#include <memory>

class Confetti {
private:
	// size of the two shape types
	const static int QUAD_SIZE = 6;
	const static int RADIUS = 10;
	std::vector<std::unique_ptr<Shape>> confetti;

public:
	// constructor
	Confetti();

	// draw the confetti on the screen
	void draw();
	
	// populate the vector of shapes
	void spawnConfetti();

	// move the confetti down and jitter to the side
	void timestep();
};


#endif
