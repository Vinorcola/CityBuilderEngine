#ifndef NATUREELEMENT_HPP
#define NATUREELEMENT_HPP

#include <QtCore/QObject>

#include "src/engine/map/MapArea.hpp"

class NatureElementInformation;

class NatureElement : public QObject
{
        Q_OBJECT

    private:
        const NatureElementInformation& conf;
        MapArea area;

    public:
        NatureElement(QObject* parent, const NatureElementInformation& conf, const MapArea& area);

        const NatureElementInformation& getConf() const;

        const MapArea& getArea() const;
};

#endif // NATUREELEMENT_HPP
