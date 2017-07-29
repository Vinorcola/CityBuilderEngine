#ifndef CONF_HPP
#define CONF_HPP

#include <QHash>

#include "global/conf/StaticElementInformation.hpp"

class Conf
{
    private:
        QHash<StaticElementInformation::Type, Owner<StaticElementInformation*>> staticElements;

    public:
        Conf(const QString& filePath);
};

#endif // CONF_HPP
