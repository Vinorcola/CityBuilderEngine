#ifndef MAP_HPP
#define MAP_HPP

#include <QVector>
#include <QSize>
#include <QBasicTimer>

#include "engine/Processable.hpp"
#include "global/MapElement.hpp"

const float MSEC_PER_SEC(1000);





/**
 * @brief Class handling a map and it's time-cycle loop.
 * 
 * The Map is the heart of the game engine. It does not handle any graphics. The graphic layer is handled by the
 * graphical client and not the engine.
 * 
 * The time-cycle loop is the loop that make the game running. It process the evolution of each buildings and units on
 * the map. The normal speed (100%) implies 75 cycles per second. The speed can be lower down, down to 10% (then, only
 * 7.5 cycles are processed each seconds).
 * 
 * @todo A no-limit speed could be eventually set, making the next cycle begin as soon as the current cycle ends.
 */
class Map : public QObject
{
        Q_OBJECT
        
    private:
        QSize size;
        QVector<Processable*> processableList;
        
        const float cyclePerSecondBase;
        float cycleRatio;
        QBasicTimer cycleClock;
        
        
        
    public:
        Map(const QSize size);
        
        
        
        /**
         * @brief Indicate if the given coordinates are valid
         * 
         * The coordinates are valid if they point to an existing cell in the map.
         */
        bool isValidCoordinates(const MapCoordinates& coordinates) const;
        
        
        
        /**
         * @brief Change the speed ratio of the time-cycle loop.
         * 
         * @param ratio A ratio between 0.1 and 1.
         */
        void setSpeedRatio(const float ratio);
        
        
        
    protected:
        /**
         * @brief Process a single time-cycle.
         * 
         * Process a single time-cycle for every processable element on the map.
         */
        virtual void timerEvent(QTimerEvent* event);
};

#endif // MAP_HPP
