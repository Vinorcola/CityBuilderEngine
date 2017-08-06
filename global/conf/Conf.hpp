#ifndef CONF_HPP
#define CONF_HPP

#include <QtCore/QHash>
#include <QtCore/QList>

#include "global/conf/ControlPanelElementInformation.hpp"
#include "global/conf/DynamicElementInformation.hpp"
#include "global/conf/StaticElementInformation.hpp"

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
