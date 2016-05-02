#ifndef BUILDING_HPP
#define BUILDING_HPP

#include "engine/characters/AbstractCharacter.hpp"
#include "engine/Processable.hpp"
#include "engine/RoadGraphNode.hpp"
#include "exceptions/OutOfRangeException.hpp"
#include "global/MapElement.hpp"





/**
 * @brief Represent a building constructed on the map.
 * 
 * This class is a base class and should not be instantiated directly.
 */
class AbstractBuilding : public Processable
{
        Q_OBJECT
        
    private:
        const int maxNumberOfWorkers;
        const int maxNumberOfWalkers;
        const MapArea location;
        
        int currentNumberOfWorkers;
        QList<AbstractCharacter*> walkerList;
        const RoadGraphNode* entryPoint;
        
        
        
        
    public:
        /**
         * @brief Construct a new building.
         * 
         * @param location The area covered by the building.
         * @param maxNumberOfWorkers The max number of people the building can employ.
         */
        AbstractBuilding(Map* map, const MapArea& location, const int maxNumberOfWorkers, const int maxNumberOfWalkers);
        
        
        
        /**
         * @brief Return the maximum number of employees that can work in the building.
         */
        int getMaxNumberOfWorkers() const;
        
        
        
        /**
         * @brief Return the maximum number of walkers on the map that belongs to the building.
         */
        int getMaxNumberOfWalkers() const;
        
        
        
        /**
         * @brief Return the area covered by the building on the map.
         */
        const MapArea& getArea() const;
        
        
        
        /**
         * @brief Return the number of employees currently working in the building.
         */
        int getCurrentNumberOfWorkers() const;
        
        
        
        /**
         * @brief Return the number of walkers on the map that belongs to the building.
         */
        int getCurrentNumberOfWalkers() const;
        
        
        
        /**
         * @brief Update the current number of employees working in the building.
         * 
         * @param numberOfWorkers The number of employees working.
         * @throw OutOfRangeException The number of employees is negative or is higher than the maximum number of employees accepted in the building.
         */
        void setCurrentNumberOfWorkers(const int numberOfWorkers) throw(OutOfRangeException);
        
        
        
        /**
         * @brief Clean the building.
         * 
         * Mainly clear any dead walker associated to the building.
         */
        void clean();
        
        
        
        /**
         * @brief Change the current entry point.
         * 
         * @param roadGraphNode The new entry point.
         */
        void setEntryPoint(const RoadGraphNode* roadGraphNode);
        
        
        
    protected:
        /**
         * @brief Register a walker created by the building.
         * 
         * This method must be used by children classes when they generate a new walker.
         * 
         * @param walker The walker to register.
         */
        void registerWalker(AbstractCharacter* walker);
};

#endif // BUILDING_HPP
