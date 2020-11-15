#ifndef NATUREELEMENT_HPP
#define NATUREELEMENT_HPP

#include <QtCore/QObject>

#include "src/engine/map/MapArea.hpp"

class NatureElementInformation;

class NatureElement
{
    private:
        const NatureElementInformation& conf;
        MapArea area;

    public:
        NatureElement(const NatureElementInformation& conf, const MapArea& area);

        const NatureElementInformation& getConf() const;
        const MapArea& getArea() const;
};

#endif // NATUREELEMENT_HPP
