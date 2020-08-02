#ifndef BUILDINGFACTORYINTERFACE_HPP
#define BUILDINGFACTORYINTERFACE_HPP

class BuildingInformation;
class MapArea;
class MapCoordinates;
class ProducerBuilding;
class StorageBuilding;

class BuildingFactoryInterface
{
    public:
        virtual ~BuildingFactoryInterface();

        virtual ProducerBuilding& generateProducer(const BuildingInformation& conf, const MapArea& area) = 0;

        virtual StorageBuilding& generateStorage(const BuildingInformation& conf, const MapArea& area) = 0;
};

#endif // BUILDINGFACTORYINTERFACE_HPP
