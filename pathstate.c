/*******************************************************
 *
 * plathstate.c
 *
 * Path generator state for path game
 *
 * Authors: T.J. Mitchell
 * Last modified: 29/06/22
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
#include "fsm.h"

/*******************************************************
 * Global variables
 *******************************************************/
tinygl_point_t *genPath = calloc (maxLength, sizeof(tinygl_point_t));
int pathLength = 0;
int maxLength = 5;

/*******************************************************
 * State actions
 *******************************************************/
void pathInit () 
{
	genPath[0].x = TINYGL_WIDTH / 2;
	genPath[0].y = TINYGL_HEIGHT / 2;
	tinygl_draw_point(genPath[0], 1);
	pathLength++;
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
	tinygl_point_t nextPos;
	tinygl_point_t emptyPositions[4];
	 
	n = checkAvailablePositions (path[pathLength], &emptyPositions);
	
	if (n > 0) {
		nextPos = chooseRand (emptyPositions, n); // may not need function
		genPath[pathLength] = nextPos;
		tinygl_draw_point (genPath[pathLength], 1);
		pathLength++;
		// delay
	} else {
		changeState (PATH_GENERATED);
	}
}

/*******************************************************/
void pathHandler ()
{
	if (pathLength > maxLength)
		stateEval (PATH_GENERATED);
}

/*******************************************************
 * Support functions
 *******************************************************/
 int checkFreePositions (tinygl_point_t currentPos, tinygl_point_t emptyPositions)
 {
	bool outOfBounds = true;
	bool taken = true;
	int n = 0;

	positions = {
		currentPos->x+=1;
		currentPos->x-=1;
		currentPos->y+=1;
		currentPos->y-=1;
	}
	
	for (int i = 0; i < 4; i ++) 
		tinygl_point_t pt = currentPos;
	
		switch (i) {
			case 0: pt->x += 1; break;
			case 1: pt->x -= 1; break;
			case 2: pt->y += 1; break;
			case 3: pt->y -= 1; break;
		}
		 
		if (!withinPath(pt) && withinBounds(pt)) {
			emptyPositions[n] = pt;
			n++;
		}
	}
	 
	return n;
 }
 
 
/*******************************************************/
 bool withinBounds (tinygl_point_t pt)
 {
	return (pt->x > 0 && pt->x < TINYGL_WIDTH && pt->y > 0 && pt->y < TINYGL_HEIGHT);
 }
 
 
/*******************************************************/
 bool withinPath (tinygl_point_t pt) 
 {
	bool isTaken;
	
	for (int j = 0; j < pathLength; j ++) {
		if (pt->x == path[j]->x && pt->y == path[j]->y) {
			isTaken = true;
		}
	}
	
	return isTaken;
 }
 
 
/*******************************************************/
 tinygl_point_t chooseRand (tinygl_point_t *array, int n)
 {
	int num = rand() % n; // random number between 0 and n
	return array[num];
 }