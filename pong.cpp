#include "pong.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "confetti.h"

Pong::Pong(int* gameDelay, int* lastTick) : box({1, 0, 0}, {350, 220}, 200, 50),
											playAgainButton(box, "Play Again?"),
                                            box2({1, 0, 0}, {340, 320}, 200, 50),
											startButton(box2, "Play") {
	// center height of screen
	int centerY = height / 2;

	// where to position user's and cpu's paddles
	int userPaddleX = paddleXOffset;
	int cpuPaddleX = width - paddleXOffset;

	// create paddles and ball
	userPaddle = Quad({1,1,1}, {userPaddleX, centerY}, paddleWidth, paddleHeight);
	cpuPaddle =  Quad({1,1,1}, {cpuPaddleX, centerY}, paddleWidth, paddleHeight);
	ball = Circle(width / 2, height / 2, ballRadius);

	// start game with a clean round
	shouldRestartRound = true;

	// set up int pointers to be able to make a delay when starting new rounds
	this->gameDelay = gameDelay;
	this->lastTick = lastTick;
}


void Pong::moveDown() {
    if(userPaddle.getBottomY() < height) {
        userPaddle.move(0, +10);
    }
}

void Pong::moveUp() {
    if(userPaddle.getTopY() > 0) {
        userPaddle.move(0, -10);
    }
}


void Pong::timestep() {
	if (shouldRestartRound) {
		startRound();
	}

	// move cpu
	double heightDifference = ball.getY() - cpuPaddle.getCenterY();
	if (heightDifference < 0) {
	    cpuPaddle.move(0, max(heightDifference, -1.0 * Pong::MAX_CPU_VELOCITY));
	} else {
	    cpuPaddle.move(0, min(heightDifference, 1.0 * Pong::MAX_CPU_VELOCITY));
	}


	// check and bounce ball off of walls and paddles
	deflectBall();

	// move ball according to its velocity
	ball.setX(ball.getX() + ballVelocity.getX());
	ball.setY(ball.getY() + ballVelocity.getY());

	// check for ball going out of play
	if (ball.getLeftX() < 0) { // goes past user
	    ++cpuScore;
		// serve ball to user
		userScoredLast = false;
		shouldRestartRound = true;
	} else if (ball.getRightX() > width) { // goes past cpu
		++userScore;
		// serve ball to cpu
		userScoredLast = true;
		shouldRestartRound = true;
	}
}

void Pong::deflectBall() {
	// power is how extreme of an angle the ball will be deflected
	// determined based on how far off center of the paddle the person hits it
	double power = 0;
	double angle = 0;

	// greatest angle that the ball can be hit at (60 degrees)
	double MAX_ANGLE = M_PI / 3;

	// if the cpu hits it
	if (ball.getRightX() > cpuPaddle.getLeftX() && cpuPaddle.getTopY() < ball.getTopY() && cpuPaddle.getBottomY() > ball.getBottomY()) {

		// how far from center of paddle the ball is 
		power = 2.0 * (cpuPaddle.getCenterY() - ball.getCenterY()) / Pong::paddleHeight;

		// calculate and set angle
		angle = power * MAX_ANGLE;
		ballVelocity.setAngle(M_PI + angle);

		// ball goes a little faster after every hit, but don't let it get beyond max magnitude
		ballVelocity.setMagnitude(min(ballVelocity.getMagnitude() * MAGNITUDE_MULTIPLIER,
									  (double) Pong::MAX_MAGNITUDE));

		// if the user hits it
	} else if (ball.getLeftX() < userPaddle.getRightX() && userPaddle.getTopY() < ball.getBottomY() && userPaddle.getBottomY() > ball.getTopY() ) {

		// how far from center of paddle the ball is 
		power = 2.0 * (userPaddle.getCenterY() - ball.getCenterY()) / Pong::paddleHeight;

		// calculate and set angle
		angle = power * MAX_ANGLE;
		ballVelocity.setAngle(angle);

		// ball goes a little faster after every hit, but don't let it get beyond max magnitude
		ballVelocity.setMagnitude(min(ballVelocity.getMagnitude() * MAGNITUDE_MULTIPLIER,
									  (double) Pong::MAX_MAGNITUDE));

		// if ball hits top or bottom of screen
	} else if (ball.getBottomY() > height && ballVelocity.getY() > 0) {
		ballVelocity *= Vec2d({1, -1});
	} else if (ball.getTopY() < 0 && ballVelocity.getY() < 0) {
		ballVelocity *= Vec2d({1, -1});
	}
}


void Pong::startRound() {
	// don't restart round again
	shouldRestartRound = false;

	// move ball to center
	ball.setX(width / 2);
	ball.setY(height / 2);
	
	// serve the ball to whoever didn't last score
	if (userScoredLast) {
		ballVelocity.set(Vec2d({5, (rand() % 30 / 10.0) * pow(-1, rand() % 2 + 1)}));	
	} else {
		ballVelocity.set(Vec2d({-5, (rand() % 30 / 10.0) * pow(-1, rand() % 2 + 1)}));
	}
	// wait 3 seconds
	*gameDelay = *lastTick + 3000;
}

// check to see if anyone's exceeded max points
bool Pong::isOver() {
	return userScore >= Pong::WINNING_SCORE || cpuScore >= Pong::WINNING_SCORE;
}

bool Pong::userWon() {
	return userScore > cpuScore;
}

void Pong::restartGame() {
	// reset scores
	userScore = 0;
	cpuScore = 0;
	// restart round and serve ball to user
	shouldRestartRound = true;
	userScoredLast = false;
}


	
// ====================
// drawing functions
// ====================

void Pong::drawStart() {
    drawString("Welcome to Pong!", 270, 150);
	glColor3f(1.0f, 0.0f, 0.0f);
    glRasterPos2i(75, 100);
	drawString("Click Play, and use the up and down arrow keys to move.", 100, 200);
	
	drawString("Press escape at any time to end.", 210, 220);
	
	startButton.draw();
}

void Pong::drawGame() {
	userPaddle.draw();
	cpuPaddle.draw();
	ball.draw();
	displayScore();
}

void Pong::drawEnd() {
	if (userScore > cpuScore) {
		drawString("You beat the Computer!", 250, 150);
	}
	if (userScore < cpuScore) {
        drawString("You lost to the Computer!", 235, 150);
	}
    if (userScore == cpuScore) {
        drawString("You tied the Computer!", 255, 150);
    }

    // Play again button
    playAgainButton.draw();
}



void Pong::displayScore() {
	// get both scores as strings
    string stringUser = to_string(userScore);
    string stringCpu = to_string(cpuScore);
	// draw them
    drawScore("User Score: ", "  CPU Score: ", stringUser, stringCpu);
}


void Pong::drawScore(string message, string message2, string userScore, string cpuScore) {
    glColor3f(1.0f, 0.0f, 0.0f);
    glRasterPos2i(225, 30);
	// draw each part of message
    for (char &letter : message) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, letter);
    }
    for (char &letter : userScore) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, letter);
    }
    for (char &letter : message2) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, letter);
    }
    for (char &letter : cpuScore) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, letter);
    }
}

// Function to draw strings
void Pong::drawString(string label, int x, int y) {
    glColor3f(1.0f, 0.0f, 0.0f);
    glRasterPos2i(x, y);
    for (char &letter : label)  {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, letter);
    }
	glEnd();
}




// ==================
// play again button
// ==================

void Pong::setPlayAgainButton(const Button &playAgainButton) {
    Pong::playAgainButton = playAgainButton;
}

const Button& Pong::getPlayAgainButton() const {
    return playAgainButton;
}

void Pong::playAgainButtonHover() {
    playAgainButton.hover();
}

void Pong::playAgainButtonRelease() {
    playAgainButton.release();
}

void Pong::playAgainButtonPressDown() {
    playAgainButton.pressDown();
}

void Pong::playAgainButtonClick() {
    playAgainButton.click(setProgramStateStart);
}



// ==================
// start again button
// ==================

void Pong::setStartButton(const Button &startButton) {
    Pong::startButton = startButton;
}

const Button& Pong::getStartButton() const {
    return startButton;
}

void Pong::startButtonHover() {
    startButton.hover();
}

void Pong::startButtonRelease() {
    startButton.release();
}

void Pong::startButtonPressDown() {
    startButton.pressDown();
}

void Pong::startButtonClick() {
	startButton.click(setProgramStateGame);
}





