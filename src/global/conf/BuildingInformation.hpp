#ifndef BUILDINGINFORMATION_HPP
#define BUILDINGINFORMATION_HPP

#include <QtCore/QList>
#include <QtCore/QString>

#include "src/global/conf/BuildingAreaInformation.hpp"
#include "src/defines.hpp"

class BuildingAreaInformation;
class BuildingSearchCriteriaDescription;
class CharacterInformation;
class ImageSequenceInformation;
class ItemInformation;
class ModelReader;
class NatureElementInformation;
namespace YAML {
    class Node;
}

class BuildingInformation
{
        Q_DISABLE_COPY_MOVE(BuildingInformation)
        friend class Conf;

    public:
        enum class Type {
            Farm,
            House,
            Laboratory,
            MapEntryPoint,
            Producer,
            Road,
            Sanity,
            School,
            Storage
        };

        struct Common {
            QString title;
            BuildingAreaInformation areaDescription;
            int maxWorkers;

            explicit Common(const ModelReader& model);
        };

        struct Graphics {
            QString mainImagePath;
            QList<owner<const ImageSequenceInformation*>> activeAnimation;

            ~Graphics();
        };

        struct WalkerGeneration {
            const CharacterInformation& conf;
            int generationInterval;
            int maxSimultaneous;

            WalkerGeneration(const CharacterInformation& conf, const int generationInterval, const int maxSimultaneous = 0);
        };

        struct Farm {
            const ItemInformation& producedItemConf;
            int harvestMonth;
            int maxQuantityHarvested;
            const CharacterInformation& deliveryManConf;

            explicit Farm(const ModelReader& model);
        };

        struct House {
            int populationPerImmigrant;
            int populationCapacity;

            explicit House(const ModelReader& model);
        };

        struct Laboratory {
            const CharacterInformation& acceptedStudent;
            int producingInterval;
            WalkerGeneration emittedScientist;

            explicit Laboratory(const ModelReader& model);
        };

        struct Producer {
            const ItemInformation& producedItemConf;
            const NatureElementInformation& rawMaterialConf;
            WalkerGeneration miner;
            int miningQuantity;
            int rawMaterialQuantityToProduce;
            int maxStoredRawMaterialQuantity;
            const CharacterInformation& deliveryManConf;

            explicit Producer(const ModelReader& model);
        };

        struct Sanity {
            WalkerGeneration walker;

            explicit Sanity(const ModelReader& model);
        };

        struct School {
            WalkerGeneration student;
            const BuildingInformation& targetLaboratory;

            explicit School(const ModelReader& model);
        };

        struct Storage {
            QList<const ItemInformation*> allowedItems;
            int maxQuantity;
            bool autoRedistribute;

            explicit Storage(const ModelReader& model);
            bool isItemAllowed(const ItemInformation& conf) const;
        };

    private:
        QString key;
        Type type;
        Common common;
        Graphics graphics;
        optional<Farm*> farm;
        optional<House*> house;
        optional<Laboratory*> laboratory;
        optional<Producer*> producer;
        optional<Sanity*> sanity;
        optional<School*> school;
        optional<Storage*> storage;

    public:
        /**
         * @brief Hold the information about a building.
         */
        explicit BuildingInformation(const ModelReader& model);
        ~BuildingInformation();

        // Generic information.
        Type getType() const;
        const QString& getTitle() const;
        const BuildingAreaInformation& getAreaDescription() const;
        MapSize getSize() const;
        int getMaxWorkers() const;

        // Graphics information.
        const Graphics& getGraphicsData() const;

        // Specific information.
        const Farm& getFarmConf() const;
        const House& getHouseConf() const;
        const Laboratory& getLaboratoryConf() const;
        const Producer& getProducerConf() const;
        const Sanity& getSanityConf() const;
        const School& getSchoolConf() const;
        const Storage& getStorageConf() const;

    private:
        void loadSpecificConf(const ModelReader& model);
        static Type resolveType(const QString& type);
};

#endif // BUILDINGINFORMATION_HPP
