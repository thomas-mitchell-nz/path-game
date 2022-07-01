/*******************************************************
 *
 * main.c
 *
 * Main program file for path game
 *
 * Authors: T.J. Mitchell
 * Last modified: 25/04/22
 *
 *******************************************************/

#include "system.h"
#include "navswitch.h"
#include "button.h"
#include "tinygl.h"
#include "pacer.h"
#include "timer.h"
#include "ledmat.h"

#include "types.h"
#include "gameengine.h"
#include "pathstate.h"
#include "menustate.h"
#include "playstate.h"

/*******************************************************
 * Constants
 *******************************************************/
#define MAX_TASKS 3
#define PACER_RATE  20
#define EVENTS_RATE 20
#define UPDATE_RATE 20
#define DRAW_RATE   20

/*******************************************************
 * Prototypes
 *******************************************************/
void init_modules (void);
void register_tasks (void);

/*******************************************************
 * Global variables
 *******************************************************/
uint8_t events_tick = 0;
uint8_t update_tick = 0;
uint8_t draw_tick = 0;

/*******************************************************
 * Support functions
 *******************************************************/
void init_modules (void)
{
    /* initialize modules */
    system_init();
    pacer_init (PACER_RATE);
}

/*******************************************************/
void register_tasks (void)
{
    /* register background tasks with kernel */
    iDupdateTask = k_register_task (currentState->handleEvents, 0, UPDATE_RATE);
    iDhandlerTask = k_register_task (currentState->update, 0, EVENTS_RATE);
    iDdrawTask = k_register_task (tinygl_update, 0 DRAW_RATE);
}

/*******************************************************
 * Main
 *******************************************************/
int main (void)
  {
    k_init (MAX_TASKS, SYSTICK_RATE); // initialize kernel

    init_modules (); // initialize modules

    register_tasks (); // register tasks with kernel

    k_start (); // start the kernel (forever)

    return 0;
}

pacer_wait ();