#ifndef DEFINES_HPP
#define DEFINES_HPP

/**
 * An alias that is used to express ownership of a pointer.
 *
 * If a method gets an Owner<T*>, it becomes responsible for deleting the pointed object if necessary. On the contrary,
 * if a method returns an Owner<T*>, it give up the responsability of deleting the pointed object.
 */
template<class T> using owner = T;

// <--- Add/Remove start between the slahes to switch.

// Normal mode.
#define CYCLE_PER_SECOND 30
#define DEBUG_TOOLS

/*/

// Developping mode.
#define CYCLE_PER_SECOND 2
#define DEBUG_TOOLS
#define SLOW_MOTION

//*/

#endif // DEFINES_HPP
