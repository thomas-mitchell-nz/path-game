#ifndef PATHSTATE_H_
#define PATHSTATE_H_

/*******************************************************
 *
 * pathstate.h
 *
 * Supports pathstate.c module
 *
 * Authors: T.J. Mitchell
 * Last modified: 01/08/22
 *
 *******************************************************/

#include "tinygl.h"

/*******************************************************
 * Prototypes
 *******************************************************/
void pathInit (void);
void pathCleanup (void);
void pathUpdate (void);
void pathHandler (void);
int checkFreePositions (tinygl_point_t currentPos, tinygl_point_t *emptyPositions);
bool withinBounds (tinygl_point_t pt);
bool withinPath(tinygl_point_t pt);

#endif 