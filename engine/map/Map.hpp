#ifndef MAP_HPP
#define MAP_HPP

#include <QLinkedList>
#include <QSize>

#include "engine/element/dynamic/AbstractDynamicMapElement.hpp"
#include "engine/element/static/AbstractStaticMapElement.hpp"
#include "engine/map/roadGraph/RoadGraph.hpp"
#include "engine/map/CityStatus.hpp"
#include "engine/map/MapSize.hpp"
#include "engine/processing/TimeCycleProcessor.hpp"
#include "global/conf/Conf.hpp"

class AbstractProcessableStaticMapElement;
class CityEntryPoint;
class TargetedWalker;

class Map : public QObject
{
        Q_OBJECT

    private:
        QSize size;
        Conf conf;
        CityStatus cityStatus;
        RoadGraph* roadGraph;
        TimeCycleProcessor* processor;
        QLinkedList<AbstractMapElement*> elementList;
        QLinkedList<AbstractStaticMapElement*> staticElementList;
        CityEntryPoint* entryPoint;

    public:
        Map(const QSize& size, const QString& confFilePath, const MapCoordinates& cityEntryPointLocation);

        virtual ~Map();

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
         * @brief Get the auto entry point coordinates.
         */
        MapCoordinates getAutoEntryPoint(const MapArea& area) const;

        /**
         * @brief Return a const reference to the time cycle processor.
         */
        const TimeCycleProcessor* getProcessor() const;

    public slots:
        /**
         * @brief Set (or unset) the pause mode.
         */
        void pause(const bool pause = true);

        /**
         * @brief Set the time-cycle processor speed ratio.
         */
        void setProcessorSpeedRatio(const qreal speedRatio);

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
        void createStaticElement(
            AbstractStaticMapElement::Type type,
            const MapArea& area
        );

        /**
         * @brief Create a dynamic element on the map.
         *
         * @param type The type of dynamic element to create.
         * @param issuer The building issuing the dynamic element.
         * @throw UnexpectedException Try to create a dynamic element of type None.
         * @return A pointer to the element created.
         */
        void createDynamicElement(
            AbstractDynamicMapElement::Type type,
            AbstractProcessableStaticMapElement* issuer,
            const int randomWalkerCredit,
            const qreal speed,
            std::function<void(AbstractDynamicMapElement*)> afterCreation
        );

        /**
         * @brief Destroy an element.
         */
        void destroyElement(
            AbstractDynamicMapElement* element,
            std::function<void()> afterDestruction
        );

        /**
         * @brief Update the total population of the given delta.
         */
        void populationChanged(const int populationDelta);

        /**
         * @brief Update the free housing capacity.
         *
         * Also requires some immigrants from the city entry point if the house still have some housing capacity.
         */
        void freeHousingCapacityChanged(
            const int previousHousingCapacity,
            const int newHousingCapacity,
            std::function<void(TargetedWalker*)> onImmigrantCreation
        );

    protected:
        AbstractStaticMapElement* fetchStaticElement(const AbstractStaticMapElement* element) const;

    signals:
        void staticElementCreated(AbstractStaticMapElement* elementCreated);
        void dynamicElementCreated(AbstractDynamicMapElement* elementCreated);
};

#endif // MAP_HPP
