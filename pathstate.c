/*******************************************************
 *
 * plathstate.c
 *
 * Path generator state for path game
 *
 * Authors: T.J. Mitchell
 * Last modified: 01/08/22
 *
 *******************************************************/

#include <stdlib.h>
#include "system.h"
#include "navswitch.h"
#include "button.h"
#include "tinygl.h"
#include "types.h"
#include "pacer.h"
#include "timer.h"
#include "ledmat.h"
#include "pathstate.h"
#include "fsm.h"

/*******************************************************
 * State actions
 *******************************************************/
void pathInit () 
{ 	
	genPath = calloc (maxLength, sizeof(tinygl_point_t));
	genPath[0].x = TINYGL_WIDTH / 2;
	genPath[0].y = TINYGL_HEIGHT / 2;
	tinygl_draw_point(genPath[0], 1);
	pathLength = 0;
}

/*******************************************************/
void pathCleanup ()
{
	tinygl_clear();
}

/*******************************************************/
void pathUpdate ()
{
	int n = 0;
	static int counter = 0;
	tinygl_point_t nextPos;
	tinygl_point_t emptyPositions[4];
	
	counter++;

	if (counter > 50 && pathLength < maxLength) {
		n = checkFreePositions (genPath[pathLength], emptyPositions);

		if (n > 0) {
			nextPos = emptyPositions[rand() % n];
			pathLength++;
			genPath[pathLength] = nextPos;
			tinygl_draw_point (genPath[pathLength], 1);
		} else {
			changeState (PATH_GENERATED);
		}

		counter = 0;
	}
}

/*******************************************************/
void pathHandler ()
{
	if (pathLength == maxLength) {
		changeState (PATH_GENERATED);
	}
}

/*******************************************************
 * Support functions
 *******************************************************/
 int checkFreePositions (tinygl_point_t pos, tinygl_point_t *emptyPositions)
 {
	tinygl_point_t temp[4] = {pos, pos, pos, pos}; // fill array with current pos
	int n = 0; // number of free positions

	// each adjacent position
	temp[0].y += 1;
	temp[1].y -= 1;
	temp[2].x -= 1;
	temp[3].x += 1;

	// iterate through each adjacent position and check whether it is free
	for (int i = 0; i < 4; i ++) {
		if (!withinPath(temp[i]) && withinBounds(temp[i])) {
			emptyPositions[n] = temp[i]; // free positions
			n++;
		}
	}
	 
	return n;
 }
 
 
/*******************************************************/
 bool withinBounds (tinygl_point_t pt)
 {
	// within bounds of LED matrix
	return (pt.x > 0 && pt.x < TINYGL_WIDTH && pt.y > 0 && pt.y < TINYGL_HEIGHT);
 }
 
 
/*******************************************************/
 bool withinPath (tinygl_point_t pt) 
 {
	bool isTaken = false;
	
	// compare with all previous points within path
	for (int j = 0; j < pathLength; j ++) { 
		if (pt.x == genPath[j].x && pt.y == genPath[j].y) {
			isTaken = true;
		}
	}
	
	return isTaken;
 }