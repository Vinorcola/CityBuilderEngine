#ifndef MAPCOORDINATES_HPP
#define MAPCOORDINATES_HPP

#include <QPointF>





/**
 * @brief Represent the coordinates of a point on a map.
 *
 * The coordinates are counted in number of tiles. Those coordinates are not necessary integers. There can be some
 * float coordinates that represent an element moving between 2 tiles. The tile pointed by the coordinates is the one
 * under the coordinate returned by the getRounded() method.
 */
class MapCoordinates
{
    private:
        QPointF coordinates;



    public:
        MapCoordinates();
        MapCoordinates(const int x, const int y);
        MapCoordinates(const qreal x, const qreal y);

        bool operator==(const MapCoordinates& other) const;
        bool operator!=(const MapCoordinates& other) const;

        bool isValid() const;
        qreal getX() const;
        qreal getY() const;

        void setX(const qreal x);
        void setY(const qreal y);

        MapCoordinates getNorth() const;
        MapCoordinates getSouth() const;
        MapCoordinates getEast() const;
        MapCoordinates getWest() const;

        MapCoordinates getRounded() const;

        // DEBUG //
        QString toString() const;
};

#endif // MAPCOORDINATES_HPP
