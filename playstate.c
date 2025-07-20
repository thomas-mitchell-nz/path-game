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
#include "playstate.h"
#include "types.h"
#include "fsm.h"

/*******************************************************
 * Global variables
 *******************************************************/
tinygl_point_t currentPos;
int playerLength = 0;
int n = 0;

/*******************************************************
 * State actions
 *******************************************************/
void playInit (void)
{
	currentPos.x = TINYGL_WIDTH / 2;
	currentPos.y = TINYGL_HEIGHT / 2;
	tinygl_draw_point(currentPos, 1);
	playerLength = 1;
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
    bool move = false; 

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

    if (move) {
        bool onPath = ptOnPath(genPath[playerLength]);
        tinygl_draw_point(currentPos, 1);
        playerLength++;

        if (onPath == true && playerLength == pathLength) {
            changeState(PATHS_MATCH);
        }

        if (onPath == false) {
            changeState(PATHS_DIFFER);
        }
    }
}

/*******************************************************
 * Support functions
 *******************************************************/
 bool ptOnPath(tinygl_point_t pt) 
 {
	return (pt.x == currentPos.x && pt.y == currentPos.y);
 }
 