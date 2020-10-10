#ifndef CONF_HPP
#define CONF_HPP

#include <QtCore/QHash>
#include <QtCore/QList>
#include <QtCore/QObject>
#include <QtCore/QString>

class BuildingInformation;
class CharacterInformation;
class ControlPanelElementInformation;
class ItemInformation;
class NatureElementInformation;

class Conf : public QObject
{
        Q_OBJECT

    private:
        QHash<QString, ItemInformation*> items;
        QHash<QString, BuildingInformation*> buildings;
        QHash<QString, CharacterInformation*> characters;
        QHash<QString, NatureElementInformation*> natureElements;
        QList<ControlPanelElementInformation*> controlPanelElements;

    public:
        Conf(QObject* parent, const QString& filePath);

        const ItemInformation& getItemConf(const QString& key) const;

        QList<QString> getAllBuildingKeys() const;

        const BuildingInformation& getBuildingConf(const QString& key) const;

        const CharacterInformation& getCharacterConf(const QString& key) const;

        QList<QString> getAllNatureElementKeys() const;

        const NatureElementInformation& getNatureElementConf(const QString& key) const;

        const QList<ControlPanelElementInformation*> getControlPanelElements() const;
};

#endif // CONF_HPP
