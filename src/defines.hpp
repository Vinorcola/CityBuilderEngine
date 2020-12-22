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



/**
 * The default quantity of processing cycles per seconds.
 */
#define CYCLES_PER_SECOND 30

/**
 * A quantity of processing cycles specific for buildings.
 */
#define BUILDING_CYCLES_PER_SECOND 1



// *** Debug feature toggle *** //

/**
 * If define, activate some debug tools.
 */
#define DEBUG_TOOLS

/**
 * If define, dynamic elements move very slowly.
 */
//#define SLOW_MOTION

/**
 * If define, display tiles' coordinates.
 */
//#define DISPLAY_COORDINATES

#endif // DEFINES_HPP
