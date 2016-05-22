#ifndef MAP_HPP
#define MAP_HPP

#include <QList>
#include <QSize>

#include "engine/element/AbstractDynamicMapElement.hpp"
#include "engine/element/AbstractStaticMapElement.hpp"
#include "engine/map/MapSize.hpp"
#include "engine/map/RoadGraph.hpp"
#include "engine/processing/TimeCycleProcessor.hpp"





class Map
{
    public:
        enum class StaticElementType
        {
            Maintenance,
            Road,
        };

        enum class DynamicElementType
        {
            RandomWalker,
        };



    private:
        QSize size;
        RoadGraph roadGraph;
        TimeCycleProcessor processor;
        QList<AbstractStaticMapElement*> staticElementList;
        QList<AbstractDynamicMapElement*> dynamicElementList;



    public:
        Map(const QSize& size);



        /**
         * @brief Return the size of the map in terms on tiles.
         */
        const QSize& getSize() const;



        /**
         * @brief getStaticElementList
         */
        const QList<AbstractStaticMapElement*>& getStaticElementList() const;



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
         * @brief Indicate if the given coordinates are free of any king of static element.
         */
        bool isFreeCoordinates(const MapCoordinates& coordinates) const;



        /**
         * @brief Indicate if the given area is free of any kind of static element.
         */
        bool isFreeArea(const MapArea& area) const;



        RoadGraph& getRoadGraph();



        TimeCycleProcessor& getProcessor();



        /**
         * @brief Create a statis element on the map.
         *
         * @param type The type of static element to create.
         * @param area The location of the element on the map.
         * @throw UnexpectedException A static element already exists on the area.
         */
        void createStaticElement(StaticElementType type, const MapArea& area);



        /**
         * @brief Create a dynamic element on the map.
         *
         * @param type The type of dynamic element to create.
         * @param initialLocation The location of the element on the map.
         */
        void createDynamicElement(DynamicElementType type, const MapCoordinates& initialLocation);
};

#endif // MAP_HPP
