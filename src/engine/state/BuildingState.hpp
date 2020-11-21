#ifndef BUILDINGSTATE_HPP
#define BUILDINGSTATE_HPP

#include <QtCore/QHash>

#include "src/engine/map/MapArea.hpp"
#include "src/defines.hpp"

class BuildingInformation;
class ItemInformation;

struct FarmState
{
    FarmState(int growthPercent) :
        growthPercent(growthPercent)
    {}

    int growthPercent;
};

struct HouseState
{
    HouseState(int inhabitants) :
        inhabitants(inhabitants)
    {}

    int inhabitants;
};

struct ProducerState
{
    ProducerState(int rawMaterialStock) :
        rawMaterialStock(rawMaterialStock)
    {}

    int rawMaterialStock;
};

struct StorageState
{
    StorageState(const QHash<const ItemInformation*, int>& stock) :
        stock(stock)
    {}

    QHash<const ItemInformation*, int> stock;
};

struct BuildingState
{
    BuildingState(qintptr id, const BuildingInformation& type, const MapArea& area, int stateVersion) :
        id(id),
        type(type),
        area(area),
        farm(nullptr),
        house(nullptr),
        producer(nullptr),
        storage(nullptr),
        stateVersion(stateVersion)
    {}

    BuildingState(const BuildingState& other) :
        id(other.id),
        type(other.type),
        area(other.area),
        farm(nullptr),
        house(nullptr),
        producer(nullptr),
        storage(nullptr),
        stateVersion(other.stateVersion)
    {
        if (other.farm) {
            farm = new FarmState(*other.farm);
        }
        if (other.house) {
            house = new HouseState(*other.house);
        }
        if (other.producer) {
            producer = new ProducerState(*other.producer);
        }
        if (other.storage) {
            storage = new StorageState(*other.storage);
        }
    }

    BuildingState& operator=(const BuildingState& other)
    {
        if (this != &other) {
            this->~BuildingState();
            new(this) BuildingState(other);
        }

        return *this;
    }

    static BuildingState CreateFarmState(
        qintptr id,
        const BuildingInformation& type,
        const MapArea& area,
        int stateVersion,
        int growthPercent
    ) {
        BuildingState state(id, type, area, stateVersion);
        state.farm = new FarmState(growthPercent);

        return state;
    }

    static BuildingState CreateHouseState(
        qintptr id,
        const BuildingInformation& type,
        const MapArea& area,
        int stateVersion,
        int inhabitants
    ) {
        BuildingState state(id, type, area, stateVersion);
        state.house = new HouseState(inhabitants);

        return state;
    }

    static BuildingState CreateProducerState(
        qintptr id,
        const BuildingInformation& type,
        const MapArea& area,
        int stateVersion,
        int rawMaterialStock
    ) {
        BuildingState state(id, type, area, stateVersion);
        state.producer = new ProducerState(rawMaterialStock);

        return state;
    }

    static BuildingState CreateStorageState(
        qintptr id,
        const BuildingInformation& type,
        const MapArea& area,
        int stateVersion,
        const QHash<const ItemInformation*, int>& stock
    ) {
        BuildingState state(id, type, area, stateVersion);
        state.storage = new StorageState(stock);

        return state;
    }

    ~BuildingState()
    {
        if (farm) {
            delete farm;
        }
        if (house) {
            delete house;
        }
        if (producer) {
            delete producer;
        }
        if (storage) {
            delete storage;
        }
    }

    qintptr id;
    const BuildingInformation& type;
    MapArea area;
    optional<owner<FarmState*>> farm;
    optional<owner<HouseState*>> house;
    optional<owner<ProducerState*>> producer;
    optional<owner<StorageState*>> storage;

    int stateVersion; ///< We use an int for the versionning of the view. Note that an overflow is not dramatic since we always compare versions using equality.
};

#endif // BUILDINGSTATE_HPP
