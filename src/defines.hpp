#ifndef DEFINES_HPP
#define DEFINES_HPP

/**
 * An alias that is used to express ownership of a pointer.
 *
 * If a method gets an owner<T*>, it becomes responsible for deleting the pointed object if necessary. On the contrary,
 * if a method returns an owner<T*>, it give up the responsability of deleting the pointed object.
 */
template<class T> using owner = T;

/**
 * An alias that is used to express the optionality of a pointer (it can be `nullptr`).
 */
template<class T> using optional = T;

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
