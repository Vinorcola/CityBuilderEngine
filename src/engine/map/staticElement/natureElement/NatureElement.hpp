#ifndef NATUREELEMENT_HPP
#define NATUREELEMENT_HPP

#include <QtCore/QObject>

#include "src/engine/map/staticElement/AbstractStaticElement.hpp"
#include "src/global/geometry/TileArea.hpp"

class NatureElementInformation;
struct NatureElementState;

class NatureElement : public AbstractStaticElement
{
    public:
        NatureElement(const NatureElementInformation& conf, const TileArea& area);

        const NatureElementInformation& getConf() const;
        const TileArea& getArea() const;

        void startInteraction();
        void endInteraction();
        bool isBusy() const;

        NatureElementState getState() const;

    private:
        const NatureElementInformation& conf;
        TileArea area;
        bool busy;
};

#endif // NATUREELEMENT_HPP
