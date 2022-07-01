/*******************************************************
 *
 * menustate.c
 *
 * Menu state for path game
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
 * State actions
 *******************************************************/
void menuInit()
{
    tinygl_text("Press button to play");
}

/*******************************************************/
void menuCleanup()
{
    tinygl_clear();
}

/*******************************************************/
void menuUpdate() { }

/*******************************************************/
void menuHandler()
{
	if ( navswitch_push_event_p(NAVSWITCH_PUSH) ) {
		changeState (SWITCH_PRESSED);
	}
}