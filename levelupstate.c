/*******************************************************
 *
 * levelupstate.c
 *
 * Level up state for path game
 *
 * Authors: T.J. Mitchell
 * Last modified: 01/08/22
 *
 *******************************************************/

#include "system.h"
#include "navswitch.h"
#include "button.h"
#include "tinygl.h"
#include "pacer.h"
#include "timer.h"
#include "ledmat.h"
#include "levelupstate.h"
#include "types.h"
#include "fsm.h"

/*******************************************************
 * State actions
 *******************************************************/
void levelupInit()
{
    tinygl_text("LEVEL UP");

	if (level < MAX_LEVEL) {
		level += 1;
		maxLength += 1; // increase level difficulty 
	}
}

/*******************************************************/
void levelupCleanup()
{
    tinygl_clear();
}

/*******************************************************/
void levelupUpdate() { }

/*******************************************************/
void levelupHandler()
{
	if ( navswitch_push_event_p(NAVSWITCH_PUSH) ) {
		changeState (BUTTON_PRESSED);
	}
}