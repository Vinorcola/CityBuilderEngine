#ifndef MAPCOORDINATES_HPP
#define MAPCOORDINATES_HPP

#include <QPointF>





class MapCoordinates
{
    private:
        QPointF coordinates;



    public:
        MapCoordinates();
        MapCoordinates(int x, int y);
        MapCoordinates(qreal x, qreal y);

        bool operator==(const MapCoordinates& other) const;
        bool operator!=(const MapCoordinates& other) const;

        bool isValid() const;
        int getX() const;
        int getY() const;
        QString toString() const;

        void setX(const int x);
        void setY(const int y);

        MapCoordinates getNorth() const;
        MapCoordinates getSouth() const;
        MapCoordinates getEast() const;
        MapCoordinates getWest() const;
};

#endif // MAPCOORDINATES_HPP
