//
// Created by Lisa Dion on 11/6/18.
//

#include "button.h"
using namespace std;

/************ Button **************/

Button::Button(Quad box, string label) {
    this->box = box;
    this->label = label;
    originalFill = box.getFill();
    hoverFill = {box.getRed()+0.5, box.getGreen()+0.5, box.getBlue()+0.5};
    pressFill = {box.getRed()-0.5, box.getGreen()-0.5, box.getBlue()-0.5};
}

void Button::draw() {
    box.draw();
    glColor3f(0, 0, 0);
    glRasterPos2i(box.getCenterX()-(4*label.length()), box.getCenterY()+7);
    for (char &letter : label) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
    }
}

/* Returns true if the coordinate is inside the box */
bool Button::isOverlapping(int x, int y) const {
	return x > box.getLeftX() && x < box.getRightX() && y > box.getTopY() && y < box.getBottomY();
}

/* Change color of the box when the user is hovering over it */
void Button::hover() {
    box.setColor(hoverFill);
}

/* Change color of the box when the user is clicking on it */
void Button::pressDown() {
    box.setColor(pressFill);
}

/* Change the color back when the user is not clicking/hovering */
void Button::release() {
    box.setColor(originalFill);
}

/* Execute whatever the Button is supposed to do */
void Button::click(function<void()> callback) {
    callback();
}

void Button::move(int x, int y) {
	box.move(x, y);
}
