#ifndef PLAYSTATE_H_
#define PLAYSTATE_H_

/*******************************************************
 *
 * playstate.h
 *
 * Supports playstate module
 *
 * Authors: T.J. Mitchell
 * Last modified: 29/06/22
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
void ptOnPath(tinygl_point_t pt);

#endif 