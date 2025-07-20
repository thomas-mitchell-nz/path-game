/*******************************************************
 *
 * menustate.c
 *
 * Menu state for path game
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
#include "pacer.h"
#include "timer.h"
#include "ledmat.h"
#include "menustate.h"
#include "fsm.h"

/*******************************************************
 * Global varaibles
 *******************************************************/
int seed = 0; // seed for random number generator 

/*******************************************************
 * State actions
 *******************************************************/
void menuInit()
{
    tinygl_text("PRESS BUTTON TO PLAY");
}

/*******************************************************/
void menuCleanup()
{
    tinygl_clear();
}

/*******************************************************/
void menuUpdate() 
{ 
	seed++; // start game time as random component to seed
}

/*******************************************************/
void menuHandler()
{
	if ( navswitch_push_event_p(NAVSWITCH_PUSH) ) {
		srand(seed); // set RNG seed
		changeState (BUTTON_PRESSED);
	}
}