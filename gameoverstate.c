/*******************************************************
 *
 * gameoverstate.c
 *
 * Gameover state for path game
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
#include "gameoverstate.h"
#include "fsm.h"

/*******************************************************
 * State actions
 *******************************************************/
void gameoverInit()
{
    tinygl_text("GAME OVER");
    maxLength = DEFAULT_LENGTH;
    level = 1;
}

/*******************************************************/
void gameoverCleanup()
{
    tinygl_clear();
}

/*******************************************************/
void gameoverUpdate() { }

/*******************************************************/
void gameoverHandler()
{
	if ( navswitch_push_event_p(NAVSWITCH_PUSH) ) {
		changeState (BUTTON_PRESSED);
	}
}