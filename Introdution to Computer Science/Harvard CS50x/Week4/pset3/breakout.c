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

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

//Font Style
#define FONT "SansSerif-48"

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

    // keep playing until game over
    waitForClick();

    double origionalXVelocity;
    double xVelocity = origionalXVelocity;
    if (xVelocity >= 1.5)
    {
      xVelocity /= -1;
    }
    double origionalYVelocity = 2.5;
    double yVelocity = origionalYVelocity;
    while (lives > 0 && bricks > 0)
    {
      updateScoreboard(window, label, points);

      move(ball, xVelocity, yVelocity);

      pause(10);

      GEvent event = getNextEvent(MOUSE_EVENT);

      if (event != NULL && getEventType(event) == MOUSE_MOVED)
      {
        int x = getX(event);
        int y = (HEIGHT / 8) * 7;
        setLocation(paddle, x, y);
      }

      GObject collisionObject = detectCollision(window, ball);

      if (collisionObject != NULL)
      {
        if(collisionObject == paddle)
        {
          yVelocity = -yVelocity;
        }
        else if (strcmp(getType(collisionObject), "GRect") == 0)
        {
          points += 1;
          removeGWindow(window, collisionObject);
          xVelocity = origionalXVelocity;
          yVelocity = origionalYVelocity;
          bricks -= 1;
        }
      }

        // left wall
        if(getX(ball) <= 0)
        {
          xVelocity = -xVelocity;
        }

        // top
        if(getY(ball) <= 0)
        {
          yVelocity = -yVelocity;
        }

        // right wall
        if(getX(ball) + getWidth(ball) >= WIDTH)
        {
          xVelocity = -xVelocity;
        }

        if(getY(ball) + getHeight(ball) >= HEIGHT)
        {
          xVelocity = 0;
          yVelocity = 0;
          lives -= 1;
          setLocation(ball ,WIDTH / 2 - RADIUS ,HEIGHT / 2 + RADIUS);
          waitForClick();
          xVelocity = 2;
          yVelocity = 2;
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
  GRect blocks[COLS][ROWS];

    // COLS ROWS
    for (int i = 0; i < ROWS; i++)
    {
      for(int j = 0; j < COLS; j++)
      {
        int spacing = 8;
        int width = 15;
        int height = (WIDTH / COLS)- 8;
        int topPadding = HEIGHT / 12;
        int sideSpacing = 1;

        GRect block = blocks[i][j];
        block = newGRect(height * j  + spacing * j + sideSpacing, width * i + spacing * i + topPadding , height , width);

        // i is colums
        if (i == 0)
        {
          setColor(block, "RED");
        }
        else if (i == 1)
        {
          setColor(block, "ORANGE");
        }
        else if (i == 2)
        {
          setColor(block, "YELLOW");
        }
        else if (i == 3)
        {
          setColor(block, "GREEN");
        }
        else if (i == 4)
        {
          setColor(block, "CYAN");
        }

        setFilled(block, true);
        add(window, block);
      }
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    GOval ball = newGOval(WIDTH / 2 - RADIUS ,HEIGHT / 2 + RADIUS , RADIUS * 2 , RADIUS * 2);
    setColor(ball, "BLACK");
    setFilled(ball, true);
    add(window, ball);
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    GRect paddle = newGRect((WIDTH / 2) - ((WIDTH / 8) * 1), (HEIGHT / 8) * 7, (WIDTH / 8) * 1, (HEIGHT / 60));
    setColor(paddle, "BLACK");
    setFilled(paddle, true);
    add(window, paddle);
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel scoreLabel = newGLabel("0");
    setFont(scoreLabel, FONT);
    setColor(scoreLabel, "LIGHT_GRAY");
    add(window, scoreLabel);
    return scoreLabel;
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
