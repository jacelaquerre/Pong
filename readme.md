# Pong


# Group Members:
* Nicholas Hanoian
* Jace Laquerre
* Nana Nimako

# Directions
This is a pong game and the main idea behind this program is to make
the computer lose. Points can be gained by either the computer or the
user by making the ball pass either side of the each other's screen.

# 3 Screens
There are three phases to this game, and they include the start screen
which has a button the user has to press to begin playing the game.
The game screen which has the two paddles and a ball. The user has to
use the up and down arrow key on the keyboard to control the paddle
where as the computer controls it own paddle to avoid the ball from
passing without getting hit. The last screen which has the score and
information how the game ended. It also has a second button that
allows you to play again and this takes you to the first screen to be
able to start a new game.

# Controls 
The game is fairly simple to use, just use the up and down arrow keys
to move the player, and use the mouse to clicke the bottons.

| Key / Button | Effect                    |
|--------------|---------------------------|
| Up arrow     | Move player's paddle up   |
| Down arrow   | Move player's paddle down |
| Left click   | Click buttons             |

# How to Win
To score a point the user has to get the ball across the field
where the cpu cannot hit it. The first to get to three points win the 
entire game and you could play again if you are willing to with the 
help of the play again button.

# Hints to help you win
* The longer the rally goes on, the faster the ball gets
* The computer can only move so fast
* The farther off the paddle's center you hit the ball, the greater the angle of
  deflection

# Polymorphism
If the player wins the game, confetti will be displayed on the end
screen. The confetti consists of Quads and Circles, which are all
stored in a vector of Shape pointers. Polymorphism is used to draw all
of these shapes in a for loop, calling the appropriate drawing method
depending on the class of the shape.
