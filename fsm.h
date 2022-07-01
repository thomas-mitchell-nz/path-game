#ifndef FSM_H_
#define FSM_H_

/*******************************************************
 *
 * fsm.h
 *
 * Supports fsm.c module
 *
 * Authors: T.J. Mitchell
 * Last modified: 29/06/2022
 *
 *******************************************************/

#include "types.h"
#include "kernel.h"

/*******************************************************
 * Prototypes
 *******************************************************/

// Configure FSM globals
void initFSM (void);

// Manage state transitions (task)
void stateManager (void);

// Trigger state transition upon function call
void changeState (event_t event);

// Finite state machine table for state transitions
state_t getNewState (state_t prevState, event_t e);

#endif /* FSM_H_ */
