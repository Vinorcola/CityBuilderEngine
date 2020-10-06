#ifndef ELEMENTHANDLER_HPP
#define ELEMENTHANDLER_HPP

#include <list>
#include <QtCore/QObject>

#include "src/engine/element/dynamic/CharacterFactoryInterface.hpp"
#include "src/engine/element/static/BuildingFactoryInterface.hpp"

class Building;
class Character;
class Map;
class MapEntryPoint;
class MapSearchEngine;
class NatureElement;
class NatureElementInformation;
class PathGenerator;
class Road;
class SanityBuilding;
class StorageBuilding;

class ElementHandler : public QObject, public BuildingFactoryInterface, public CharacterFactoryInterface
{
        Q_OBJECT

    private:
        Map& map;
        MapSearchEngine& searchEngine;
        const PathGenerator& pathGenerator;
        std::list<Building*> buildings;
        std::list<Character*> characters;
        std::list<NatureElement*> natureElements;

    public:
        ElementHandler(Map& map, MapSearchEngine& searchEngine, const PathGenerator& pathGenerator);

        // Buildings

        const std::list<Building*>& getBuildings() const;

        virtual FarmBuilding& generateFarm(const BuildingInformation& conf, const MapArea& area) override;

        virtual HouseBuilding& generateHouse(const BuildingInformation& conf, const MapArea& area) override;

        virtual LaboratoryBuilding& generateLaboratory(const BuildingInformation& conf, const MapArea& area) override;

        virtual ProducerBuilding& generateProducer(const BuildingInformation& conf, const MapArea& area) override;

        virtual SanityBuilding& generateSanity(const BuildingInformation& conf, const MapArea& area) override;

        virtual SchoolBuilding& generateSchool(const BuildingInformation& conf, const MapArea& area) override;

        virtual StorageBuilding& generateStorage(const BuildingInformation& conf, const MapArea& area) override;

        Road& generateRoad(const BuildingInformation& conf, const MapCoordinates& location);

        // Characters

        const std::list<Character*>& getCharacters() const;

        virtual DeliveryManCharacter& generateDeliveryMan(
            const CharacterInformation& conf,
            ProcessableBuilding& issuer,
            const ItemInformation& transportedItemConf,
            const int transportedQuantity = 0
        ) override;

        virtual ImmigrantCharacter& generateImmigrant(
            const CharacterInformation& conf,
            const MapCoordinates& initialLocation,
            ProcessableBuilding& issuer
        ) override;

        virtual MinerCharacter& generateMiner(
            const CharacterInformation& conf,
            ProcessableBuilding& issuer,
            owner<PathInterface*> path
        ) override;

        virtual StudentCharacter& generateStudent(
            const CharacterInformation& conf,
            ProcessableBuilding& issuer,
            ProcessableBuilding& target
        ) override;

        virtual WanderingCharacter& generateWanderingCharacter(
            const CharacterInformation& conf,
            ProcessableBuilding& issuer
        ) override;

        virtual void clearCharacter(Character& character) override;

        // Nature elements

        const std::list<NatureElement*>& getNatureElements() const;

        NatureElement& generateNatureElement(const NatureElementInformation& conf, const MapArea& area);

    signals:
        void buildingCreated(Building& building);
        void characterCreated(Character& character);
        void natureElementCreated(NatureElement& natureElement);

        void characterDestroyed(Character* invalidPointerToDeletedCharacter);

    private:
        void canConstructBuilding(const BuildingInformation& conf, const MapArea& area);
};

#endif // ELEMENTHANDLER_HPP
