#ifndef ABSTRACTPROCESSABLE
#define ABSTRACTPROCESSABLE

#include "engine/processing/TimeCycleProcessor.hpp"





/**
 * @brief Represent a processable element on the map.
 * 
 * A processable element is an element that exists on the map, and that its state will evolve during time. There are 2
 * main kind of processable elements: buildings and characters.
 * 
 * The process() method is called to process on single time-cycle. Each processbla can do want it wants during this
 * time-cycle. For example, a character can moves whil a builing can generate a character.
 */
class AbstractProcessable
{
    public:
        AbstractProcessable();



        /**
         * @brief Process a single time-cycle.
         */
        virtual void process(const CycleDate& date) = 0;
};

#endif // ABSTRACTPROCESSABLE
