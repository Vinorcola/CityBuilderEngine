#ifndef TILECOORDINATES_HPP
#define TILECOORDINATES_HPP

#include <QtCore/QString>

class DynamicElementCoordinates;
class QPoint;

/**
 * @brief The coordinates of a tile on the map.
 */
class TileCoordinates
{
    public:
        TileCoordinates(int x, int y);
        TileCoordinates(const TileCoordinates& other, const QPoint& offset);
        bool operator ==(const TileCoordinates& other) const;
        bool operator !=(const TileCoordinates& other) const;

        int x() const;
        int y() const;
        const QString& hash() const;

        DynamicElementCoordinates toDynamicElementCoordinates() const;

        // Distances.
        int manhattanDistanceTo(const TileCoordinates& other) const;
        qreal chebyshevDistanceTo(const TileCoordinates& other) const;
        qreal straightDistanceTo(const TileCoordinates& other) const;

        // Invalid coordinates (try to see if we can avoid this).
        TileCoordinates();
        bool isValid() const;

    private:
        int _x;
        int _y;
        QString _hash;
};

#endif // TILECOORDINATES_HPP
