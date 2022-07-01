#ifndef TYPES_H_
#define TYPES_H_

/*******************************************************
 *
 * types.h
 *
 * Supports typedefs globally
 *
 * Authors: T.J. Mitchell
 * Date modified: 25/04/2022
 *
 *******************************************************/

#include <stdint.h>
#include "kernel.h"

/*******************************************************
 * Typedefs
 *******************************************************/
typedef void (*action)(); // function pointer type

typedef enum {
    NULL_STATE,
    MENU_STATE,
    PATH_STATE,
    PLAY_STATE
} stateiD_t; // possible states

typedef enum {
    BUTTON_PRESSED,
    PATH_GENERATED,
    PATHS_MATCH,
    PATHS_DIFFER
} event_t; // possible events

typedef struct {
    stateId_t id; // state index
    action handler; // events handler
    action update;
    action draw;
    action cleanup;
} state_t; // state data type

typedef struct {
    state_t index,
    void* init(),
    void* cleanup(),
    void* update(),
    void* handleEvents()
} stateElem_t;

/*******************************************************
 * Global variables
 *******************************************************/
state_t currentState; // current system state

// task ids
taskId_t iDupdateTask;
taskId_t iDhandlerTask;
taskId_t iDdrawTask;

#endif /* TYPES_H_ */