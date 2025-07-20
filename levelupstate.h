#ifndef LEVELUPSTATE_H_
#define LEVELUPSTATE_H_

/*******************************************************
 *
 * levelupstate.h
 *
 * Supports levelupstate.c module
 *
 * Authors: T.J. Mitchell
 * Last modified: 01/08/22
 *
 *******************************************************/

/*******************************************************
 * Prototypes
 *******************************************************/
void levelupInit (void);
void levelupCleanup (void);
void levelupUpdate (void);
void levelupHandler (void);

#endif 