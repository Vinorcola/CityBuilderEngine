#ifndef CONF_HPP
#define CONF_HPP

#include <QtCore/QHash>
#include <QtCore/QList>
#include <QtCore/QObject>
#include <QtCore/QString>

class BuildingInformation;
class CharacterInformation;
class ControlPanelElementInformation;

class Conf : public QObject
{
        Q_OBJECT

    private:
        QHash<QString, CharacterInformation*> dynamicElements;
        QHash<QString, BuildingInformation*> staticElements;
        QList<ControlPanelElementInformation*> controlPanelElements;

    public:
        Conf(QObject* parent, const QString& filePath);

        const CharacterInformation* getDynamicElementConf(const QString& elementKey) const;

        const BuildingInformation* getStaticElementConf(const QString& elementKey) const;

        const QList<ControlPanelElementInformation*> getControlPanelElements() const;
};

#endif // CONF_HPP
