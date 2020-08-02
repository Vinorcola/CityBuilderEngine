#ifndef BUILDINGINFORMATION_HPP
#define BUILDINGINFORMATION_HPP

#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QString>
#include <QtGui/QPixmap>

#include "src/engine/map/MapSize.hpp"
#include "src/defines.hpp"

class BuildingAreaPartDescription;
class BuildingSearchCriteriaDescription;
class CharacterInformation;
class ItemInformation;
class ModelReader;
class NatureElementInformation;
namespace YAML {
    class Node;
}

class BuildingInformation : public QObject
{
        Q_OBJECT

    public:
        enum class Type {
            Producer,
            Road
        };

        struct Common {
            QString title;
            MapSize size;
            int price;
            int employees;
            int fireRiskIncrement;
            int damageRiskIncrement;
            QList<BuildingAreaPartDescription*> areaDescription;

            explicit Common(const ModelReader& model);
        };

        struct Graphics {
            QPixmap image;

            explicit Graphics(const ModelReader& model);
        };

        struct WalkerGeneration {
            const CharacterInformation& conf;
            int generationInterval;
            int maxSimultaneous;

            WalkerGeneration(const CharacterInformation& conf, const int generationInterval, const int maxSimultaneous);
        };

        struct Producer {
            const ItemInformation& producedItemConf;
            const NatureElementInformation& rawMaterialConf;
            WalkerGeneration miner;
            int miningQuantity;
            int rawMaterialQuantityToProduce;
            int maxStoredRawMaterialQuantity;

            explicit Producer(const ModelReader& model);
        };

    private:
        QString key;
        Type type;
        Common common;
        Graphics graphics;
        optional<Producer*> producer;

    public:
        /**
         * @brief Hold the information about a building.
         */
        BuildingInformation(QObject* parent, const ModelReader& model);

        virtual ~BuildingInformation();

        Type getType() const;

        const QString& getTitle() const;

        const MapSize& getSize() const;

        const Producer& getProducerConf() const;

        const QPixmap& getImage() const;

    private:
        static Type resolveType(const QString& type);
};

#endif // BUILDINGINFORMATION_HPP
