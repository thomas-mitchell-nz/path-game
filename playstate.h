#ifndef PLAYSTATE_H_
#define PLAYSTATE_H_

/*******************************************************
 *
 * playstate.h
 *
 * Supports playstate.c module
 *
 * Authors: T.J. Mitchell
 * Last modified: 01/08/22
 *
 *******************************************************/

#include "tinygl.h"

/*******************************************************
 * Prototypes
 *******************************************************/
void playInit (void);
void playCleanup (void);
void playUpdate (void);
void playHandler (void);
bool ptOnPath(tinygl_point_t pt);

#endif 