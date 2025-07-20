/*******************************************************
 *
 * fsm.c
 *
 * Implements finite state machine
 *
 * Authors: T.J. Mitchell
 * Last modified: 01/08/22
 *
 *******************************************************/

#include "types.h"
#include "fsm.h"
#include "kernel.h"
#include "menustate.h"
#include "pathstate.h"
#include "playstate.h"
#include "levelupstate.h"
#include "gameoverstate.h"

/*******************************************************
 * Global variables
 *******************************************************/

// State types containing function pointers
state_t menuState = {MENU_STATE, menuInit, menuHandler, menuUpdate, menuCleanup};
state_t pathState = {PATH_STATE, pathInit, pathHandler, pathUpdate, pathCleanup};
state_t playState = {PLAY_STATE, playInit, playHandler, playUpdate, playCleanup};
state_t gameoverState = {GAMEOVER_STATE, gameoverInit, gameoverHandler, gameoverHandler, gameoverCleanup};
state_t levelupState = {LEVELUP_STATE, levelupInit, levelupHandler, levelupUpdate, levelupCleanup};

/*******************************************************
 * Configure FSM globals
 *******************************************************/
void initFSM (void)
{
    currentState = menuState;
    currentState.init ();
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

    unregisterState ();

    currentState.init ();

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
        if ( e == BUTTON_PRESSED ) newState = pathState;
        break;
    case PATH_STATE:
        if ( e == PATH_GENERATED) newState = playState;
        break;
    case PLAY_STATE:
        if ( e == PATHS_MATCH ) newState = levelupState;
        else if ( e == PATHS_DIFFER ) newState = gameoverState;
        break;
    case LEVELUP_STATE:
        if ( e == BUTTON_PRESSED ) newState = pathState;
        break;
    case GAMEOVER_STATE:
        if ( e == BUTTON_PRESSED) newState = menuState;
        break;
    default: // state on startup
        newState =  menuState;
    }

    return newState;
}

/*******************************************************
 * Register state functions as individual tasks
 *******************************************************/
void registerState (state_t newState)
{
    iDstateUpdate = k_register_task (newState.update, UPDATE_RATE);
    iDstateHandler = k_register_task (newState.handler, EVENTS_RATE);
}

/*******************************************************
 * Unregister state functions
 *******************************************************/
void unregisterState (void)
{
    k_unregister_task (iDstateHandler);
    k_unregister_task (iDstateUpdate);
}