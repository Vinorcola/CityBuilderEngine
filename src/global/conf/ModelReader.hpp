#ifndef MODELREADER_HPP
#define MODELREADER_HPP

#include <QtCore/QString>

#include "src/engine/map/MapCoordinates.hpp"

class BuildingInformation;
class CharacterInformation;
class Conf;
class ItemInformation;
class NatureElementInformation;
namespace YAML {
    class Node;
}

class ModelReader
{
    private:
        const Conf& conf;
        const QString& key;
        const YAML::Node& node;

    public:
        ModelReader(const Conf& conf, const QString& key, const YAML::Node& node);

        const QString& getKey() const;
        const YAML::Node& getNode() const;
        const ModelReader getSubModel(const char key[]) const;

        bool getOptionalBool(const char key[], const bool defaultValue) const;

        int getInt(const char key[]) const;
        int getOptionalInt(const char key[], const int defaultValue) const;

        qreal getReal(const char key[]) const;

        QString getString(const char key[]) const;
        QString getOptionalString(const char key[], const QString& defaultValue) const;

        MapCoordinates getMapCoordinates(const char key[]) const;

        QPoint getPoint(const char key[]) const;
        QPoint getOptionalPoint(const char key[], const QPoint& defaultValue) const;
        QList<QPoint> getPointList(const char key[]) const;
        QList<QPoint> getOptionalPointList(const char key[]) const;

        const BuildingInformation& getBuildingConf(const char key[]) const;

        const CharacterInformation& getCharacterConf(const char key[]) const;
        const CharacterInformation& getOptionalCharacterConf(const char key[], const CharacterInformation& defaultValue) const;
        const CharacterInformation& getOptionalCharacterConf(const char key[], const QString defaultValue) const;

        const ItemInformation& getItemConf(const char key[]) const;
        QList<const ItemInformation*> getListOfItemConfs(const char key[]) const;

        const NatureElementInformation& getNatureElementConf(const char key[]) const;

    private:
        const QString generateErrorMessage(const char key[], const char expected[]) const;
};

#endif // MODELREADER_HPP
