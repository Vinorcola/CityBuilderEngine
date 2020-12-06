#include "MapSize.hpp"

#include <cassert>
#include <QtCore/QString>



MapSize::MapSize(int size) :
    size(size, size)
{
    assert(size > 0);
}



MapSize::MapSize(int width, int height) :
    size(width, height)
{
    assert(width > 0);
    assert(height > 0);
}



bool MapSize::isSquare() const
{
    return size.width() == size.height();
}



int MapSize::getWidth() const
{
    return size.width();
}



int MapSize::getHeight() const
{
    return size.height();
}



QString MapSize::toString() const
{
    return '(' + QString::number(size.width()) + 'x' + QString::number(size.height()) + ')';
}
