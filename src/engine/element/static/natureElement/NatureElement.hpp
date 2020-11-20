#ifndef NATUREELEMENT_HPP
#define NATUREELEMENT_HPP

#include <QtCore/QObject>

#include "src/engine/map/MapArea.hpp"
#include "src/engine/state/NatureElementState.hpp"

class NatureElementInformation;

class NatureElement
{
    private:
        NatureElementState state;

    public:
        NatureElement(const NatureElementInformation& conf, const MapArea& area);

        NatureElementState getState() const;
};

#endif // NATUREELEMENT_HPP
