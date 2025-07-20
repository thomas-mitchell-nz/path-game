#ifndef GAMEOVERSTATE_H_
#define GAMEOVERSTATE_H_

/*******************************************************
 *
 * gameoverstate.h
 *
 * Supports gameoverstate.c module
 *
 * Authors: T.J. Mitchell
 * Last modified: 01/08/22
 *
 *******************************************************/

/*******************************************************
 * Prototypes
 *******************************************************/
void gameoverInit (void);
void gameoverCleanup (void);
void gameoverUpdate (void);
void gameoverHandler (void);

#endif 