#ifndef CONF_HPP
#define CONF_HPP

#include <QtCore/QHash>
#include <QtCore/QList>
#include <QtCore/QObject>
#include <QtCore/QString>

class ControlPanelElementInformation;
class DynamicElementInformation;
class StaticElementInformation;

class Conf : public QObject
{
        Q_OBJECT

    private:
        QHash<QString, DynamicElementInformation*> dynamicElements;
        QHash<QString, StaticElementInformation*> staticElements;
        QList<ControlPanelElementInformation*> controlPanelElements;

    public:
        Conf(QObject* parent, const QString& filePath);

        const DynamicElementInformation* getDynamicElementConf(const QString& elementKey) const;

        const StaticElementInformation* getStaticElementConf(const QString& elementKey) const;

        const QList<ControlPanelElementInformation*> getControlPanelElements() const;
};

#endif // CONF_HPP
