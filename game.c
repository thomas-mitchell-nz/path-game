/*******************************************************
 *
 * main.c
 *
 * Main program file for path game
 *
 * Authors: T.J. Mitchell
 * Last modified: 01/08/22
 *
 *******************************************************/

#include <string.h>
#include "system.h"
#include "navswitch.h"
#include "button.h"
#include "tinygl.h"
#include "pacer.h"
#include "timer.h"
#include "ledmat.h"
#include "../fonts/font3x5_1.h"

#include "types.h"
#include "fsm.h"
#include "kernel.h"
#include "pathstate.h"
#include "menustate.h"
#include "playstate.h"

/*******************************************************
 * Constants
 *******************************************************/
#define MAX_TASKS   20
#define PACER_RATE  300

/*******************************************************
 * Prototypes
 *******************************************************/
void init_modules (void);
void register_tasks (void);
void text_init (void);

/*******************************************************
 * Support functions
 *******************************************************/
 void text_init (void)
{
    tinygl_font_set (&font3x5_1);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_text_dir_set (TINYGL_TEXT_DIR_ROTATE);
    tinygl_text_speed_set (10);
}

/*******************************************************/
void init_modules (void)
{
    system_init ();
    ledmat_init ();
    text_init ();
    tinygl_init (PACER_RATE);
    navswitch_init ();
    initFSM ();
    level = 1;
    maxLength = DEFAULT_LENGTH;
}

/*******************************************************/
void register_tasks (void)
{
    /* register background tasks with kernel */
    iDdrawTask = k_register_task (tinygl_update, DRAW_RATE);
    iDnavswitchTask = k_register_task (navswitch_update, EVENTS_RATE);
}

/*******************************************************
 * Main
 *******************************************************/
int main (void)
  {
    k_init (MAX_TASKS, PACER_RATE); // initialize kernel

    init_modules (); // initialize modules

    register_tasks (); // register tasks with kernel

    k_start (); // start the kernel (forever)

    return 0;
}