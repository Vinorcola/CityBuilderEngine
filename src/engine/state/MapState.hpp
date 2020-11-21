#ifndef MAPSTATE_HPP
#define MAPSTATE_HPP

#include <QtCore/QSize>

struct MapState
{
    MapState(const QSize& size) :
        size(size)
    {}

    QSize size;
};

#endif // MAPSTATE_HPP
