#ifndef PATHSTATE_H_
#define PATHSTATE_H_

/*******************************************************
 *
 * pathstate.h
 *
 * Supports pathstate module
 *
 * Authors: T.J. Mitchell
 * Last modified: 25/04/22
 *
 *******************************************************/

#include "tinygl.h"

/*******************************************************
 * Prototypes
 *******************************************************/
void pathInit ();
void pathCleanup ();
void pathUpdate ();
void pathHandler ();
int checkFreePositions (tinygl_point_t currentPos, tinygl_point_t emptyPositions);
bool withinBounds (tinygl_point_t pt);
tinygl_point_t chooseRand (tinygl_point_t *array);
bool withinPath(tinygl_point_t pt);

#endif 