#include "TileAreaSize.hpp"

#include <cassert>
#include <QtCore/QString>



TileAreaSize::TileAreaSize(int width) :
    TileAreaSize(width, width)
{

}



TileAreaSize::TileAreaSize(int width, int height) :
    _width(width),
    _height(height)
{
    assert(width >= 1);
    assert(height >= 1);
}



bool TileAreaSize::isSquare() const
{
    return _width == _height;
}



int TileAreaSize::width() const
{
    return _width;
}



int TileAreaSize::height() const
{
    return _height;
}



QString TileAreaSize::toString() const
{
    return '(' + QString::number(_width) + 'x' + QString::number(_height) + ')';
}
