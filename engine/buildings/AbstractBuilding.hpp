#ifndef BUILDING_HPP
#define BUILDING_HPP

#include "engine/Processable.hpp"
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
        const int maxWorkers;
        int currentWorkers;
        
        const MapArea location;
        
        
        
    public:
        /**
         * @brief Construct a new building.
         * 
         * @param location The area covered by the building.
         * @param maxEmployees The max number of people the building can employ.
         */
        AbstractBuilding(const MapArea& location, const int maxWorkers);
        
        
        
        /**
         * @brief Return the maximum number of employees that can work in the building.
         */
        int getMaxWorkers() const;
        
        
        
        /**
         * @brief Return the number of employees currently working in the building.
         */
        int getCurrentWorkers() const;
        
        
        
        /**
         * @brief Update the current number of employees working in the building.
         * 
         * @param workers The number of employees working.
         * @throw OutOfRangeException The number of employees is negative or is higher than the maximum number of employees accepted in the building.
         */
        void setCurrentWorkers(const int workers) throw(OutOfRangeException);
};

#endif // BUILDING_HPP
