#ifndef CONF_HPP
#define CONF_HPP

#include <QHash>

#include "global/conf/DynamicElementInformation.hpp"
#include "global/conf/StaticElementInformation.hpp"

class Conf : public QObject
{
        Q_OBJECT

    private:
        QHash<DynamicElementInformation::Type, DynamicElementInformation*> dynamicElements;
        QHash<StaticElementInformation::Type, StaticElementInformation*> staticElements;

    public:
        Conf(QObject* parent, const QString& filePath);

        const DynamicElementInformation* getDynamicElementConf(DynamicElementInformation::Type type) const;

        const StaticElementInformation* getStaticElementConf(StaticElementInformation::Type type) const;
};

#endif // CONF_HPP
