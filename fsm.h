#ifndef FSM_H_
#define FSM_H_

/*******************************************************
 *
 * fsm.h
 *
 * Supports fsm.c module
 *
 * Authors: T.J. Mitchell
 * Last modified: 01/08/2022
 *
 *******************************************************/

#include "types.h"
#include "kernel.h"

/*******************************************************
 * Global variables
 *******************************************************/
 
 // state ids for state tasks
taskId_t iDstateUpdate;
taskId_t iDstateHandler;

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

// Register state handler and update tasks
void registerState (state_t newState);

// Unregister state handler and update tasks
void unregisterState (void);

#endif /* FSM_H_ */
