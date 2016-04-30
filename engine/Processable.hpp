#ifndef PROCESSABLE
#define PROCESSABLE

#include <QObject>





/**
 * @brief Represent a processable element on the map.
 * 
 * A processable element is an element that exists on the map, and that its state will evolve during time. There are 2
 * main kind of processable elements: buildings and characters.
 * 
 * The process() method is called to process on single time-cycle. Each processbla can do want it wants during this
 * time-cycle. For example, a character can moves whil a builing can generate a character.
 */
class Processable : public QObject
{
        Q_OBJECT
        
    public:
        /**
         * @brief Destruct the processable element.
         */
        virtual ~Processable() {}
        
        
        
        /**
         * @brief Process a single time-cycle.
         */
        virtual void process() = 0;
};

#endif // PROCESSABLE
