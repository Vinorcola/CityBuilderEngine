#ifndef ABSTRACTPROCESSABLE
#define ABSTRACTPROCESSABLE

#include "engine/processing/TimeCycleProcessor.hpp"





/**
 * @brief Represent a processable element on the map.
 * 
 * A processable element is an element that exists on the map, and that its state will evolve during time. There are 2
 * main kinds of processable elements: buildings and characters.
 * 
 * The init() method is called when registering the element in the time-cycle processor. The process() method is called
 * to process on single time-cycle. Each processable can do what it wants during this time-cycle. For example, a
 * character can moves while a builing can generate a character.
 */
class AbstractProcessable
{
    public:
        AbstractProcessable();
        virtual ~AbstractProcessable();

        /**
         * @brief Init the processable element with the current date.
         */
        virtual void init(const CycleDate& /*date*/) {}

        /**
         * @brief Process a single time-cycle.
         */
        virtual void process(const CycleDate& date) = 0;
};

#endif // ABSTRACTPROCESSABLE
