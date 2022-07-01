/*******************************************************
 *
 * playstate.c
 *
 * Play game state for path game
 *
 * Authors: T.J. Mitchell
 * Last modified: 25/04/22
 *
 *******************************************************/

#include "system.h"
#include "navswitch.h"
#include "button.h"
#include "tinygl.h"
#include "pacer.h"
#include "timer.h"
#include "ledmat.h"
#include "gameengine.h"
#include "playstate.h"

/*******************************************************
 * Global variables
 *******************************************************/
tinygl_point_t currentPos;
int n = 0;

/*******************************************************
 * State actions
 *******************************************************/
void playInit (void)
{
	currentPos->x = TINYGL_WIDTH / 2;
	currentPos->y = TINYGL_HEIGHT / 2;
	tinygl_draw_point(currentPos[0], 1);
	pathLength++;
}

/*******************************************************/
void playCleanup (void)
{
    tinygl_clear ();
}

/*******************************************************/
void playUpdate (void) { }

/*******************************************************/
void playHandler (void)
{
    if (navswitch_push_event_p(NAVSWITCH_WEST)) {
        currentPos.x--;
        move = true;
    }

    if (navswitch_push_event_p(NAVSWITCH_EAST)) {
        currentPos.x++;
        move = true;
    }

    if (navswitch_push_event_p(NAVSWITCH_SOUTH)) {
        currentPos.y++;
        move = true;
    }

    if (navswitch_push_event_p(NAVSWITCH_NORTH)) {
        currentPos.y--;
        move = true;
    }

    if (move && ptOnPath(currentPos)) {
        tinygl_draw_point(currentPos, 1);
	} else if (move) {
        tinygl_text("Game Over")
		stateEval(PATHS_DIFFER);
	}
		
	if (n == maxLength) {
        tinygl_text("Level Up")
        // increase path length
		stateEval(PATHS_MATCH);
	} else {
		n++;
	}
}

/*******************************************************
 * Support functions
 *******************************************************/
 void ptOnPath(tinygl_point_t pt) 
 {
	return (pt->x == path[n]->x && pt->y == path[n]->y);
 }
 