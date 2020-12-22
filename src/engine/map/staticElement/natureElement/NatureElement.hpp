#ifndef NATUREELEMENT_HPP
#define NATUREELEMENT_HPP

#include <QtCore/QObject>

#include "src/global/state/NatureElementState.hpp"

class NatureElementInformation;

class NatureElement
{
    private:
        NatureElementState state;

    public:
        NatureElement(const NatureElementInformation& conf, const TileArea& area);

        NatureElementState getState() const;
};

#endif // NATUREELEMENT_HPP
