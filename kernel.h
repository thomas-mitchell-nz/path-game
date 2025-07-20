#ifndef KERNEL_H_
#define KERNEL_H_

/*******************************************************
 *
 * kernel.h
 *
 * Supports kernel.c module
 *
 * Authors: T.J. Mitchell
 * Last modified: 01/08/22
 *
 *******************************************************/

#include <stdint.h>
#include <stdbool.h>

/*******************************************************
 * Typedefs
 *******************************************************/
typedef uint16_t taskId_t; // taskId type

// Task state and handler entry point
typedef struct {
    taskId_t id; // Unique task ID
    bool ready; // Ready/Blocked?
    uint8_t freq; // Tick rate
    uint8_t tick; // Task tick counter
    void (*run) (void); // Task pointer
} Task_t;

/*******************************************************
 * Global variables
 *******************************************************/
uint8_t num_registered_tasks;
uint8_t scheduler_max_tasks;
Task_t *scheduled_task; // pointer to array of scheduled tasks
uint8_t tick_rate;

/*******************************************************
 * Prototypes
 *******************************************************/

// initialize kernel for up to 'maxTasks' tasks and set up system clock
void k_init (uint8_t maxTasks, uint32_t tickRate);

// register task with kernel. return unique id
taskId_t k_register_task (void (*taskEnter) (void), uint8_t rate);

// start the round-robin scheduling of the set of registered and "ready" tasks
void k_start (void);

// remove nominated task from kernel. The task can be subsequently re-registered
void k_unregister_task (taskId_t taskId);

// notify nominated task so it will be executed by scheduler
void k_notify_task (taskId_t taskId);

// block nominated task so it will not be executed by scheduler
void k_block_task (taskId_t taskId);

// return the task with the corresponding taskId
Task_t *get_task (taskId_t taskId);

// generate unique id
taskId_t generate_id (void);

#endif /* KERNEL_H_ */
