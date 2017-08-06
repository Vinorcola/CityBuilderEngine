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
        QHash<QString, StaticElementInformation*> staticElements;

    public:
        Conf(QObject* parent, const QString& filePath);

        const DynamicElementInformation* getDynamicElementConf(DynamicElementInformation::Type type) const;

        const StaticElementInformation* getStaticElementConf(const QString& elementKey) const;
};

#endif // CONF_HPP
