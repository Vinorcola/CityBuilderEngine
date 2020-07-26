#ifndef MAP_HPP
#define MAP_HPP

#include <functional>
#include <QtCore/QLinkedList>
#include <QtCore/QObject>
#include <QtCore/QSize>

#include "src/engine/map/pathFinder/MapDetailsInterface.hpp"
#include "src/engine/map/TraversableLocationCache.hpp"

class BehaviorFactory;
class Building;
class BuildingInformation;
class Character;
class CharacterInformation;
class CityEntryPoint;
class CityStatus;
class Conf;
class CycleDate;
class MapArea;
class MapCoordinates;
class MapLoader;
class NatureElement;
class NatureElementInformation;
class ProcessableBuilding;
class RoadGraph;
class RoadGraphNode;
class SearchEngine;
class TimeCycleProcessor;

class Map : public QObject, public MapDetailsInterface
{
        Q_OBJECT

    private:
        const Conf* conf;
        QSize size;
        CityStatus* cityStatus;
        RoadGraph* roadGraph;
        TimeCycleProcessor* processor;
        SearchEngine* searchEngine;
        BehaviorFactory* behaviorFactory;
        QLinkedList<Character*> characterList;
        QLinkedList<Building*> buildingList;
        QLinkedList<NatureElement*> natureElementList;
        TraversableLocationCache traversableLocationCache;
        CityEntryPoint* entryPoint;

    public:
        Map(const Conf* conf, const MapLoader& loader);

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
         * @brief Resolve the road graph node corresponding to the given coordinates.
         *
         * It returns `nullptr` if there is no road at those coordinates.
         */
        const RoadGraphNode* resolveRoad(const MapCoordinates& coordinates) const;

        /**
         * @brief Get shortest road path between two coordinates.
         *
         * It returns a list of road nodes to go through or an empty list if there is not path available between the
         * given coordinates.
         */
        QList<const RoadGraphNode*> getShortestRoadPathBetween(
            const MapCoordinates& origin,
            const MapCoordinates& destination
        ) const;

        /**
         * @brief Get the auto entry point around the given area.
         */
        MapCoordinates getAutoEntryPoint(const MapArea& area) const;

        /**
         * @brief Return a const reference to the time cycle processor.
         */
        const TimeCycleProcessor* getProcessor() const;

        /**
         * @brief Return the list of all buildings.
         */
        const QLinkedList<Building*>& getBuildings() const;

        /**
         * @brief Return the list of all characters.
         */
        const QLinkedList<Character*>& getCharacters() const;

        /**
         * @brief Return the list of all nature elements.
         */
        const QLinkedList<NatureElement*>& getNatureElements() const;

        /**
         * @brief Get current budget.
         */
        int getCurrentBudget() const;

        /**
         * @brief Get the current population.
         */
        int getCurrentPopulation() const;

        /**
         * @brief Get the current date for display purpose.
         */
        const CycleDate& getCurrentDate() const;

        virtual bool isLocationTraversable(const MapCoordinates& location) const;

        virtual bool isLocationARoad(const MapCoordinates& location) const;

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
         * @brief Create a building on the map.
         *
         * If the area is not free, the element is not created. For now, we just log with qDebug(). But this fail should
         * be kept silent because it could eventually append in real condition when a static element creation request
         * append while the area get "unfree" during the last time cycle process.
         *
         * @param conf The conf for the new building to create.
         * @param area The location of the element on the map.
         * @throw UnexpectedException Try to create a static element of type None.
         */
        void createBuilding(const BuildingInformation* conf, const MapArea& area);

        /**
         * @brief Create a character on the map.
         *
         * @param conf          The conf for the new character to create.
         * @param issuer        The building issuing the character.
         * @param afterCreation A callback that will be called with the created character as first argument.
         * @throw UnexpectedException Try to create a dynamic element of type None.
         */
        void createCharacter(
            const CharacterInformation* conf,
            ProcessableBuilding* issuer,
            std::function<void(Character*)> afterCreation
        );

        /**
         * @brief Create a nature element on the map.
         * @param conf The conf for the new nature element to create.
         * @param area The location of the element on the map.
         */
        void createNatureElement(const NatureElementInformation* conf, const MapArea& area);

        /**
         * @brief Destroy a building.
         */
        void destroyBuilding(Building* building, std::function<void()> afterDestruction);

        /**
         * @brief Destroy a character.
         */
        void destroyCharacter(Character* character, std::function<void()> afterDestruction);

        /**
         * @brief Update the total population of the given delta.
         */
        void changePopulation(const int populationDelta);

        /**
         * @brief Update the free housing capacity.
         *
         * Also requires some immigrants from the city entry point if the house still have some housing capacity.
         */
        void freeHousingCapacityChanged(
            const int previousHousingCapacity,
            const int newHousingCapacity,
            std::function<void(Character*)> onImmigrantCreation
        );

    protected:
        Building* fetchBuilding(const Building* building) const;

    signals:
        void buildingCreated(Building* building);
        void characterCreated(Character* character);
        void natureElementCreated(NatureElement* natureElement);
        void budgetChanged(const int budget);
        void populationChanged(const int population);
        void dateChanged(const int year, const int month);
};

#endif // MAP_HPP
