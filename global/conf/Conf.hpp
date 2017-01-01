#ifndef CONF_HPP
#define CONF_HPP

#include <QHash>

#include "global/conf/StaticElementInformation.hpp"

template<typename StaticElementInformation> using Onwer = StaticElementInformation;





class Conf
{
    private:
        QHash<StaticElementInformation::Type, Owner<StaticElementInformation*>> staticElements;



    public:
        Conf(const QString& filePath);
};

#endif // CONF_HPP
