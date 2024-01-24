/*******************************************************
 *
 * kernel.c
 *
 * System kernel for task scheduling
 *
 * Authors: T.J. Mitchell
 * Last modified:  01/08/22
 *
 *******************************************************/

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "kernel.h"
#include "types.h"
#include "pacer.h"
#include "system.h"

/*******************************************************
 * Interrupt handler for the SysTick interrupt
 *******************************************************/
void SysTickIntHandler (void)
{
    uint8_t i;

    // loop over task array elements
    for (i = 0; i < num_registered_tasks; i++) {
        scheduled_task[i].tick++; // increment task tick counter

        // if frequency condition met
        if (scheduled_task[i].tick >= (tick_rate/scheduled_task[i].freq)) {
            k_notify_task (scheduled_task[i].id); // notify task scheduler
            scheduled_task[i].tick = 0; // reset tick counter
        }
    }
}

/*******************************************************
 * Kernel functions
 *******************************************************/
void k_init(uint8_t maxTasks, uint32_t tickRate)
{
    /* initialize kernel; for up to 'maxTasks' tasks and set up system clock*/

    // Set kernel parameters
    num_registered_tasks = 0;
    scheduler_max_tasks = maxTasks;
    tick_rate = tickRate;

    // initialize pacer
    pacer_init (tickRate);
}

/*******************************************************/
taskId_t k_register_task (void (*taskEnter) (void), uint8_t rate)
{
    /* register task with kernel */
    Task_t newTask = { // create new task
        .id = generate_id (), // generate unique id
        .ready = false,
        .freq = rate,
        .tick = 0,
        .run = taskEnter // define task function pointer
    };


    if (num_registered_tasks < scheduler_max_tasks) {
        num_registered_tasks++; // increment task counter
        // resize tasks array
        scheduled_task = realloc (scheduled_task, num_registered_tasks * sizeof(Task_t));
        scheduled_task[num_registered_tasks-1] = newTask; // define new task
        return newTask.id; // return unique task id
    }

    return newTask.id; //////////////////////////////////////////////////////////////////////
}

/*******************************************************/
void k_start (void)
{
    /* Starts the round-robin scheduling of the set of registered and "ready" tasks */
    while (true) { // infinite loop
        SysTickIntHandler ();
        pacer_wait ();

        for (uint8_t i = 0; i < num_registered_tasks; i++) {
            if (scheduled_task[i].ready) {
                scheduled_task[i].ready = false;
                scheduled_task[i].run(); // Call task handler
            }
        }
    }
}

/*******************************************************/
void k_unregister_task (taskId_t taskId)
{
    /* remove nominated task from kernel */
    int i, j;

    // search array for task
    for (i = 0; i < num_registered_tasks; i++) {
        if (scheduled_task[i].id == taskId) {
            break;
        }
    }

    // if taskId found
    if (i < num_registered_tasks) {
        num_registered_tasks--; // decrement task counter

        // shift tasks backward
        for (j = i; j < num_registered_tasks; j++) {
            scheduled_task[j] = scheduled_task[j+1];
        }

        // resize tasks array
        scheduled_task = realloc (scheduled_task, num_registered_tasks * sizeof(Task_t));
    }
}

/*******************************************************/
void k_notify_task (taskId_t taskId)
{
    /* notify nominated task so it will be executed by scheduler */
    Task_t *myTask = get_task (taskId); // retrieve task from taskId

    if (myTask != NULL) { // if corresponding task is registered
        myTask->ready = true; // notify task
    }
}

/*******************************************************/
void k_block_task (taskId_t taskId)
{
    /* block nominated task so it wont be executed by scheduler */
    Task_t *myTask = get_task (taskId); // retrieve task from taskId

    if (myTask != NULL) { // if corresponding task is registered
        myTask->ready = false; // block task
    }
}

/*******************************************************
 * Support functions: generate_id, get_task
 *******************************************************/
taskId_t generate_id (void)
{
    /* increment counter to generate unique id */
    static int32_t counter = 0;
    return counter++;
}

/*******************************************************/
Task_t *get_task (taskId_t taskId)
{
    /* return task corresponding to taskId */
    uint8_t i;

    for (i = 0; i < num_registered_tasks; i++) { // loop over task array elements
        if (scheduled_task[i].id == taskId) { // if current element corresponds to taskId
            return scheduled_task+i; // return pointer to array element
        }
    }

    return NULL; // return NULL if task not identified
}
