#ifndef PONG_H
#define PONG_H

#define _USE_MATH_DEFINES
#include <math.h>
#include "circle.h"
#include "graphics.h"
#include "shapes.h"
#include "quad.h"
#include "button.h"
#include "vec2d.h"
#include "confetti.h"
using namespace std;




class Pong {
private:
	// size and position of paddles and ball
	const static int paddleXOffset = 20;
	const static int paddleHeight = 70;
	const static int paddleWidth = 10;
	const static int ballRadius = 8;

	const static int MAX_CPU_VELOCITY = 5;
	const static int WINNING_SCORE = 3;
	const double MAGNITUDE_MULTIPLIER = 1.1; // couldn't make static (compiler error)
	const static int MAX_MAGNITUDE = 30;
	
	int* gameDelay;
	int* lastTick;

	// buttons
	Quad box;
	Quad box2;
	Button playAgainButton;
	Button startButton;

	// paddles
	Quad userPaddle;
	Quad cpuPaddle;

	// ball and its velocity
	Circle ball;
	Vec2d ballVelocity;

	// score and flow
	bool shouldRestartRound;
	bool userScoredLast;
	int userScore;
	int cpuScore;

	// confetti when the user wins
	Confetti confetti;

public:
	const static int width = 700;
	const static int height = 500;

	// constructor takes in pointers to ints which allow for setting a
	// delay for ball movement (before a new round starts)
	Pong(int* gameDelay, int* lastTick);


	// ====================
	// game functions
	// ====================

	// move player up and down
	void moveUp();
	void moveDown();

	// move ball and cpu
	void timestep();

	// check for ball collisions with paddles and sides and bounce accordingly
	// called from timestep function
	void deflectBall();

	void startRound();

	// whether the game is over or not (score greater than max)
	bool isOver();

	// return whether or not the user won
	bool userWon();
	
	// reset scores to 0 and restart round
	void restartGame();


	
	// ====================
	// drawing functions
	// ====================

	// functions to draw each screen
    void drawStart();
	void drawGame();
	void drawEnd();

	
	// show score on game screen
    void displayScore();
	// helper function to display everything
    void drawScore(string message, string message2, string userScore, string cpuScore);


	// display a string on the screen
    void drawString(string label, int x, int y);


	// ==================
	// buttons
	// ==================
	
	// start button
	const Button &getStartButton() const;
	void setStartButton(const Button &button1);
    void startButtonHover();
    void startButtonRelease();
    void startButtonPressDown();
    void startButtonClick();


	// play again button
	const Button &getPlayAgainButton() const;	
	void setPlayAgainButton(const Button &button);
	void playAgainButtonHover();
	void playAgainButtonRelease();
	void playAgainButtonPressDown();
    void playAgainButtonClick();



};


#endif
