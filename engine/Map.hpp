#ifndef MAP_HPP
#define MAP_HPP

#include <QBasicTimer>
#include <QObject>
#include <QSize>
#include <QVector>

#include "exceptions/InvalidMapElementException.hpp"
#include "global/MapElement.hpp"

class AbstractBuilding;
class AbstractCharacter;
class Processable;
class RoadGraphNode;

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
        const float cyclePerSecondBase;
        const int numberOfCycleBetweenCleans;
        
        QSize size;
        QVector<Processable*> processableList;
        QVector<AbstractBuilding*> buildingList;
        float cycleRatio;
        QBasicTimer cycleClock;
        int numberOfCyclesElapsed;
        QList<RoadGraphNode*> roadGraphNodeList;
        
        
        
    public:
        Map(const QSize size);
        
        
        
        /**
         * @brief Indicate if the given coordinates are valid
         * 
         * The coordinates are valid if they point to an existing cell in the map.
         */
        bool isValidCoordinates(const MapCoordinates& coordinates) const;
        
        
        
        /**
         * @brief Indicate if the given area is valid.
         * 
         * The area is valid if it fits on the map.
         */
        bool isValidArea(const MapArea& area) const;
        
        
        
        /**
         * @brief Change the speed ratio of the time-cycle loop.
         * 
         * @param ratio A ratio between 0.1 and 1.
         */
        void setSpeedRatio(const float ratio);
        
        
        
        /**
         * @brief Register a building on the map.
         * 
         * @param building The building to register.
         */
        void registerBuilding(AbstractBuilding* building) throw (InvalidMapElementException);
        
        
        
        /**
         * @brief Register a character on the map.
         * 
         * @param character The character to register.
         */
        void registerCharacter(AbstractCharacter* character);
        
        
        
        /**
         * @brief Remove the processable from the map.
         * 
         * @note The element is removed from the map, but not deleted. Please take care to delete it.
         * 
         * @param processable The processable element to remove.
         */
        void removeProcessable(Processable* processable);
        
        
        
        /**
         * @brief Fetch the road graph node located and the given coordinate, or nullptr if no road exists at those coordinates.
         */
        RoadGraphNode* fetchRoadGraphNodeAt(const MapCoordinates& coordinates);
        
        
        
    protected:
        /**
         * @brief Process a single time-cycle.
         * 
         * Process a single time-cycle for every processable element on the map.
         */
        virtual void timerEvent(QTimerEvent* event);
        
        
        
    private:
        /**
         * @brief Fetch the first road graph node find arroung the building or nullptr if not was found.
         */
        RoadGraphNode* fetchRoadGraphNodeArround(const MapArea& area);
};

#endif // MAP_HPP
