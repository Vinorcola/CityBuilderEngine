#ifndef BUILDINGSTATE_HPP
#define BUILDINGSTATE_HPP

#include <QtCore/QHash>

#include "src/global/geometry/TileArea.hpp"
#include "src/global/BuildingStatus.hpp"
#include "src/global/Direction.hpp"
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
    BuildingState(
        qintptr id,
        const BuildingInformation& type,
        const TileArea& area,
        Direction orientation,
        BuildingStatus status,
        int workers,
        int stateVersion
    ) :
        id(id),
        type(type),
        area(area),
        orientation(orientation),
        status(status),
        workers(workers),
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
        orientation(other.orientation),
        status(other.status),
        workers(other.workers),
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
        const TileArea& area,
        Direction orientation,
        BuildingStatus status,
        int workers,
        int stateVersion,
        int growthPercent
    ) {
        BuildingState state(id, type, area, orientation, status, workers, stateVersion);
        state.farm = new FarmState(growthPercent);

        return state;
    }

    static BuildingState CreateHouseState(
        qintptr id,
        const BuildingInformation& type,
        const TileArea& area,
        Direction orientation,
        BuildingStatus status,
        int workers,
        int stateVersion,
        int inhabitants
    ) {
        BuildingState state(id, type, area, orientation, status, workers, stateVersion);
        state.house = new HouseState(inhabitants);

        return state;
    }

    static BuildingState CreateProducerState(
        qintptr id,
        const BuildingInformation& type,
        const TileArea& area,
        Direction orientation,
        BuildingStatus status,
        int workers,
        int stateVersion,
        int rawMaterialStock
    ) {
        BuildingState state(id, type, area, orientation, status, workers, stateVersion);
        state.producer = new ProducerState(rawMaterialStock);

        return state;
    }

    static BuildingState CreateStorageState(
        qintptr id,
        const BuildingInformation& type,
        const TileArea& area,
        Direction orientation,
        BuildingStatus status,
        int workers,
        int stateVersion,
        const QHash<const ItemInformation*, int>& stock
    ) {
        BuildingState state(id, type, area, orientation, status, workers, stateVersion);
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
    TileArea area;
    Direction orientation;
    BuildingStatus status;
    int workers;
    optional<owner<FarmState*>> farm;
    optional<owner<HouseState*>> house;
    optional<owner<ProducerState*>> producer;
    optional<owner<StorageState*>> storage;

    int stateVersion; ///< We use an int for the versionning of the view. Note that an overflow is not dramatic since we always compare versions using equality.
};

#endif // BUILDINGSTATE_HPP
