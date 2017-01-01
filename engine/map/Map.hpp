#ifndef MAP_HPP
#define MAP_HPP

#include <QList>
#include <QSize>

#include "engine/element/AbstractDynamicMapElement.hpp"
#include "engine/element/AbstractStaticMapElement.hpp"
#include "engine/map/MapSize.hpp"
#include "engine/map/RoadGraph.hpp"
#include "engine/processing/TimeCycleProcessor.hpp"
#include "global/conf/Conf.hpp"





class Map : public QObject
{
        Q_OBJECT


    public:
        enum class StaticElementType
        {
            None = 0,
            Maintenance,
            Road,
        };

        enum class DynamicElementType
        {
            None = 0,
            RandomWalker,
        };



    private:
        QSize size;
        Conf conf;
        RoadGraph roadGraph;
        TimeCycleProcessor processor;
        QList<QSharedPointer<AbstractStaticMapElement>> staticElementList;
        QList<QSharedPointer<AbstractDynamicMapElement>> dynamicElementList;



    public:
        Map(const QSize& size, const QString& confFilePath);



        /**
         * @brief Return the size of the map in terms on tiles.
         */
        const QSize& getSize() const;



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



        /**
         * @brief Return a const reference to the time cycle processor.
         */
        const TimeCycleProcessor& getProcessor() const;



    public slots:
        /**
         * @brief Create a static element on the map.
         *
         * If the area is not free, the element is not created. For now, we just log with qDebug(). But this fail should
         * be kept silent because it could eventually append in real condition when a static element creation request
         * append while the area get "unfree" during the last time cycle process.
         *
         * @param type The type of static element to create.
         * @param area The location of the element on the map.
         * @throw UnexpectedException Try to create a static element of type None.
         */
        void createStaticElement(StaticElementType type, const MapArea& area);



        /**
         * @brief Create a dynamic element on the map.
         *
         * @param type The type of dynamic element to create.
         * @param initialLocation The location of the element on the map.
         * @throw UnexpectedException Try to create a dynamic element of type None.
         */
        void createDynamicElement(DynamicElementType type, const MapCoordinates& initialLocation);



    signals:
        void staticElementCreated(const QWeakPointer<AbstractStaticMapElement>& elementCreated);
        void dynamicElementCreated(const QWeakPointer<AbstractDynamicMapElement>& elementCreated);
};

#endif // MAP_HPP
