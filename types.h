#ifndef TYPES_H_
#define TYPES_H_

/*******************************************************
 *
 * types.h
 *
 * Contains global typedefs and variables
 *
 * Authors: T.J. Mitchell
 * Date modified: 25/04/2022
 *
 *******************************************************/

#include <stdint.h>
#include "kernel.h"
#include "tinygl.h"

/*******************************************************
 * Constants
 *******************************************************/
#define EVENTS_RATE     20
#define UPDATE_RATE     20
#define DRAW_RATE       30
#define MAX_LEVEL       10
#define DEFAULT_LENGTH  5

/*******************************************************
 * Typedefs
 *******************************************************/
typedef void (*action)(void); // function pointer type

typedef enum {
    MENU_STATE,
    PATH_STATE,
    PLAY_STATE,
    GAMEOVER_STATE,
    LEVELUP_STATE
} stateId_t; // possible states

typedef enum {
    BUTTON_PRESSED,
    PATH_GENERATED,
    PATHS_MATCH,
    PATHS_DIFFER
} event_t; // possible events

typedef struct {
    stateId_t id; // state index
    action init;
    action handler; // events handler
    action update;
    action cleanup;
} state_t; // state data type

/*******************************************************
 * Global variables
 *******************************************************/
state_t currentState; // current system state
tinygl_point_t *genPath; // pointer to array which stores path coordinates
uint8_t maxLength; // max path length for current level
uint8_t level; // current level
uint8_t pathLength; // generated path length 

// task ids
taskId_t iDupdateTask;
taskId_t iDhandlerTask;
taskId_t iDdrawTask;
taskId_t iDnavswitchTask;

#endif /* TYPES_H_ */