#include "graphics.h"
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <math.h>
#include "shapes.h"
#include "circle.h"
#include "pong.h"
#include "button.h"
#include <time.h>
using namespace std;

GLdouble width, height;
int wd;
int lastTick;
int gameDelay;

Pong pong(&gameDelay, &lastTick);
Confetti confetti;

// keep track of whether each key is pressed down
// used to keep track of arrow keys, so that we don't have to deal
// with key repeat when moving up and down
bool keyState[256] = {false};

// for storing what screen we're on
enum state {start, game, end};
state programState;

// go to start screen
void setProgramStateStart() {
	programState = state::start;
	pong.restartGame();
}

// go to game screen
void setProgramStateGame() {
	programState = state::game;
}

void init() {
	width = Pong::width;
	height = Pong::height;
	lastTick = 0;
	// start high so that ball doesn't move until after delay (gets
	// reset to the correct level by pong.startRound(), this is just
	// to make sure it doesn't move before that gets set)
	gameDelay = 1000;

	// set random seed
	srand (time(NULL));
}

/* Initialize OpenGL Graphics */
void initGL() {
	// Set "clearing" or background color
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black and opaque
}

/* Handler for window-repaint event. Call back when the window first appears and
   whenever the window needs to be re-painted. */
void display() {
    // tell OpenGL to use the whole window for drawing
    glViewport(0, 0, width, height);
    
    // do an orthographic parallel projection with the coordinate
    // system set to first quadrant, limited by screen/window size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, width, height, 0.0, -1.f, 1.f);
    
    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer with current clearing color
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// decided what to display
    switch(programState) {
	case state::start: {
		pong.drawStart();
		break;
	}
	case state::game: {
		pong.drawGame();
		// if we reach max score, go to end screen
		if (pong.isOver()) {
			programState = state::end;
		}
		break;
	}
	case state::end: {
		pong.drawEnd();
		if (pong.userWon()) {
			confetti.draw();
		}
		break;
	}
    }
	glFlush();  // Render now
	timer(0); // start timer to redraw
}

// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
// handles escape to end game
void kbd(unsigned char key, int x, int y)
{
    // escape
    if (key == 27) {
        glutDestroyWindow(wd);
        exit(0);
    }
	
	// uncomment to allow using 'a' to manually switch between screens
	// else if (key == 97) {
	// 	if (programState == state::start) {
	// 		programState = state::game;			
	// 	} else if (programState == state::game) {
	// 		programState = state::end;
	// 	} else {
	// 		programState = state::start;
	// 	}
	// }
	glutPostRedisplay();
}



// https://cboard.cprogramming.com/game-programming/80515-glut-keyboard-reaction-help.html
// method found from link above. instead of reacting when a key is
// pressed, we flip a bool to true when it is initially pressed, and
// when we detect that it's released, we set that bool back to false.
// Each timestep, we can check to see whether that key is pressed
// down, and act accordingly
void keySpecialDownFunc(int key, int x, int y) {
	keyState[key] = true;
	glutPostRedisplay();
}
void keySpecialUpFunc(int key, int x, int y) {
	keyState[key] = false;
	glutPostRedisplay();
}

// For play again button
void cursor(int x, int y) {
    if (pong.getPlayAgainButton().isOverlapping(x, y)) {
        pong.playAgainButtonHover();
    } else {
        pong.playAgainButtonRelease();
    }

    if (pong.getStartButton().isOverlapping(x, y)) {
        pong.startButtonHover();
    } else {
        pong.startButtonRelease();
    }
    glutPostRedisplay();
}

// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {
	// start button
	if (programState == state::start) {

		if (state == GLUT_DOWN &&
			button == GLUT_LEFT_BUTTON &&
			pong.getStartButton().isOverlapping(x, y)) {
			pong.startButtonPressDown();
		} else {
			pong.startButtonRelease();
		}

		if (state == GLUT_UP &&
			button == GLUT_LEFT_BUTTON &&
			pong.getStartButton().isOverlapping(x, y)) {
			pong.startButtonClick();
		}
	}

	// play again button
	if (programState == state::end) {
		if (state == GLUT_DOWN &&
			button == GLUT_LEFT_BUTTON &&
			pong.getPlayAgainButton().isOverlapping(x, y)) {
			pong.playAgainButtonPressDown();
		} else {
			pong.playAgainButtonRelease();
		}

		if (state == GLUT_UP &&
			button == GLUT_LEFT_BUTTON &&
			pong.getPlayAgainButton().isOverlapping(x, y)) {
			pong.playAgainButtonClick();
		}
	}

	glutPostRedisplay();
}

// https://gamedev.stackexchange.com/questions/1589/when-should-i-use-a-fixed-or-variable-time-step
// modified a bit so that we have constant time instead of relying on
// glut's built in timer, we effectively create our own glut can
// repaint the window as often as it wants, but we determine when the
// game physics get updated. This prevents inconsistent game speeds.
void timer(int dummy) {
	// get when last tick was
	int tick = glutGet(GLUT_ELAPSED_TIME);

	// if it's not time to move everything, then don't do anything
	if (tick < lastTick) {
		return;
	}
	// while we're "behind" tick until we're ahead again
	while (tick > lastTick) {
		// make sure we're in the game, and then allow user to move and game to go
		if (programState == state::game) {
			// move up and down
			if (keyState[GLUT_KEY_UP]) {
				pong.moveUp();
			}
			if (keyState[GLUT_KEY_DOWN]) {
				pong.moveDown();
			}
			// additional delay to allow for delay between game rounds
			if (tick > gameDelay) {
				pong.timestep();
			}
		} else if (programState == state::end && pong.userWon()) {
			confetti.timestep();
		}

		// target 45 fps, and wait for us to get there
		lastTick += 1000 / 45;
		
	}
	// repaint window
	glutPostRedisplay();
}


// dummy function to call display from glut's timer
void callDisplay(int dummy) {
	display();
	glutPostRedisplay();
	glutTimerFunc(10, callDisplay, 10);
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
    
    init();
    
    glutInit(&argc, argv); // Initialize GLUT
    
    glutInitDisplayMode(GLUT_RGBA);
    
    glutInitWindowSize((int)width, (int)height);
    glutInitWindowPosition(-100, 400); // Position the window's initial top-left corner
    /* create the window and store the handle to it */
    wd = glutCreateWindow("Game of Pong" /* title */ );
    
    // Register callback handler for window re-paint event
    glutDisplayFunc(display);
    
    // Our own OpenGL initialization
    initGL();

	// register keyboard press event processing function
    // works for numbers, letters, spacebar, etc.
    glutKeyboardFunc(kbd);

	// register pressing down and releasing special keys
	glutSpecialFunc(keySpecialDownFunc);
	glutSpecialUpFunc(keySpecialUpFunc);

	// don't repeat key presses
	glutIgnoreKeyRepeat(true);

    // handles mouse movement
    glutPassiveMotionFunc(cursor);
    
    // handles mouse click
    glutMouseFunc(mouse);
    
    // handles timer (we use our own which is called from display so
    // we just use callDisplay to allow us to call the display
    // function with an argument)
    glutTimerFunc(10, callDisplay, 10);

	// Enter the event-processing loop
    glutMainLoop();
    return 0;
}
