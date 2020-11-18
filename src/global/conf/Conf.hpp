#ifndef CONF_HPP
#define CONF_HPP

#include <QtCore/QHash>
#include <QtCore/QList>
#include <QtCore/QSize>
#include <QtCore/QString>

#include "src/defines.hpp"

class BuildingInformation;
class CharacterInformation;
class ControlPanelElementInformation;
class ItemInformation;
class NatureElementInformation;

class Conf
{
        Q_DISABLE_COPY_MOVE(Conf)

    private:
        QSize tileSize;
        QHash<QString, owner<ItemInformation*>> items;
        QHash<QString, owner<BuildingInformation*>> buildings;
        QHash<QString, owner<CharacterInformation*>> characters;
        QHash<QString, owner<NatureElementInformation*>> natureElements;
        QList<owner<ControlPanelElementInformation*>> controlPanelElements;

    public:
        explicit Conf(const QString& filePath);
        ~Conf();

        const QSize& getTileSize() const;

        const ItemInformation& getItemConf(const QString& key) const;

        QList<QString> getAllBuildingKeys() const;

        const BuildingInformation& getBuildingConf(const QString& key) const;

        QList<QString> getAllCharacterKeys() const;

        const CharacterInformation& getCharacterConf(const QString& key) const;

        QList<QString> getAllNatureElementKeys() const;

        const NatureElementInformation& getNatureElementConf(const QString& key) const;

        const QList<ControlPanelElementInformation*> getControlPanelElements() const;
};

#endif // CONF_HPP
