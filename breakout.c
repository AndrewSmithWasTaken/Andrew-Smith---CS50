//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// paddle height and width
#define PADDLEHEIGHT 5
#define PADDLEWIDTH 60

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;

    // initial velocity
    double x_velocity = drand48();
    double y_velocity = 2.0;

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        // follow mouse forever
        while (true)
        {
            // check for mouse event
            GEvent event = getNextEvent(MOUSE_EVENT);

            // if we heard one
            if (event != NULL)
            {
                // if the event was movement
                if (getEventType(event) == MOUSE_MOVED)
                {
                    // ensure paddle moves along x axis
                    double x = getX(event) - getWidth(paddle) / 2;
                    double y = 580;
                    setLocation(paddle, x, y);
                }
            }

            // store object for collision detection
            GObject object = detectCollision(window, ball);

            // move ball
            move(ball, x_velocity, y_velocity);

            // bounce off right edge of window
            if (getX(ball) + getWidth(ball) >= getWidth(window))
            {
                x_velocity = -x_velocity;
            }
            // bounce off left edge of window
            else if (getX(ball) <= 0)
            {
                x_velocity = -x_velocity;
            }
            // when ball hits bottom of window, reset ball and paddle
            else if (getY(ball) + getHeight(ball) >= getHeight(window))
            {
                if ( lives == 1 )
                {
                    lives--;
                    break;
                }
                else
                {
                    lives--;
                    setLocation(ball, 190, 290);
                    setLocation(paddle, 170, 580);
                    waitForClick();
                }
            }
            // bounce off top of window
            else if (getY(ball) <= 0)
            {
                y_velocity = -y_velocity;
            }

            // detect ball hitting paddle or bricks
            detectCollision(window, ball);
            if (object == paddle)
            {
                y_velocity = -abs(y_velocity);
            }
            else if (object!=NULL && strcmp(getType(object), "GRect") == 0)
                {
                    y_velocity = -y_velocity;
                    removeGWindow(window, object);
                    bricks--;
                    points++;
                    updateScoreboard(window, label, points);
                }
            // linger before moving again
            pause(10);
        }
    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    int bwidth = 30;
    int bheight = 10;
    int xcoord = 5;
    int ycoord = 50;
    int xgap=  40;
    int ygap = 15;
    char* colors[] = {"RED", "YELLOW", "CYAN", "MAGENTA", "BLUE"};

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            GRect brick = newGRect(xcoord, ycoord, bwidth, bheight);
            setFilled(brick, true);
            setColor(brick, colors[i]);
            add(window, brick);
            xcoord = xcoord + xgap;
        }
        ycoord = ycoord + ygap;
        xcoord = xcoord - (xgap * 10);
    }
}
/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    GOval oval = newGOval(190, 290, RADIUS*2, RADIUS*2);
    setFilled(oval, true);
    setColor(oval, "BLACK");
    add(window, oval);
    return oval;
}
/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    GRect paddle = newGRect(170, 580, PADDLEWIDTH, PADDLEHEIGHT);
    setFilled(paddle, true);
    setColor(paddle, "BLACK");
    add(window, paddle);
    return paddle;
}
/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel label = newGLabel("0");
    setFont(label, "SansSerif-38");
    setLocation(label, ((getWidth(window) - getWidth(label)) / 2), ((getHeight(window) - getHeight(label)) / 2));
    add(window, label);
    return label;
}
/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}
/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
