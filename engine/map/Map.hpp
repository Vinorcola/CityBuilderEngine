#ifndef MAP_HPP
#define MAP_HPP

#include <QList>
#include <QSize>

#include "engine/map/MapSize.hpp"
#include "engine/map/RoadGraph.hpp"
#include "engine/processing/TimeCycleProcessor.hpp"

class AbstractMapElement;





class Map
{
    private:
        QSize size;
        RoadGraph roadGraph;
        TimeCycleProcessor processor;
        QList<AbstractMapElement*> elementList;



    public:
        Map(const QSize& size);



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
         * @brief Indicate if the given coordinates are free of any king of element occupying an area on the map (tipically, motionless elements).
         */
        bool isFreeCoordinates(const MapCoordinates& coordinates) const;



        /**
         * @brief Indicate if the given area is free of any kind of element occupying an area on the map (tipically, motionless elements).
         */
        bool isFreeArea(const MapArea& area) const;



        /**
         * @brief register an element on the map.
         *
         * @param element The element to register
         * @throw UnexpectedException If the element is a motionless element and it's area is not free.
         */
        void registerElement(AbstractMapElement* element);



        /**
         * @brief Unregister an element that exists on the map.
         *
         * @param element The element to unregister.
         */
        void unregisterElement(AbstractMapElement* element);



        RoadGraph& getRoadGraph();



        TimeCycleProcessor& getProcessor();
};

#endif // MAP_HPP
