/*******************************************************
 *
 * fsm.c
 *
 * Implements finite state machine for milestone2
 *
 * Authors: S.G. Jackson & T.J. Mitchell
 * Last modified:  26/04/22
 *
 *******************************************************/

#include "types.h"
#include "fsm.h"
#include "kernel.h"

/*******************************************************
 * Global variables
 *******************************************************/

// State types containing function pointers
state_t menuState = {MENU_STATE, menuHandler, menuUpdate, menuCleanup};
state_t pathState = {PATH_STATE, pathHandler, pathUpdate, pathCleanup};
state_t playState = {PLAY_STATE, playHandler, playUpdate, playCleanup};

/*******************************************************
 * Configure FSM globals
 *******************************************************/
void initFSM (void)
{
    currentState = menuState;
    registerState (currentState);
}

/*******************************************************
 * Trigger state transition upon function call
 *******************************************************/
void changeState (event_t event)
{
    state_t prevState = currentState;

    currentState = getNewState (prevState, event);

    prevState.cleanup ();

    unregisterState (prevState);

    registerState (currentState);
}

/*******************************************************
 * Finite state machine table for state transitions
 *******************************************************/
state_t getNewState (state_t prevState, event_t e)
{
    state_t newState;

    // Finite state machine
    switch ( prevState.id )
    {
    case MENU_STATE:
        if ( e == BUTTON_PRESS ) newState = pathState;
        break;
    case PATH_STATE:
        if ( e == PATH_GENERATED ) newState = playState;
        break;
    case PLAY_STATE:
        if ( e == PATHS_MATCH ) newState = pathState;
        else if ( e == PATHS_DIFFER ) newState = menuState;
        break;
    default: // state on startup
        newState =  menuState;
    }

    return newState;
}