#ifndef MAPCOORDINATES_HPP
#define MAPCOORDINATES_HPP

#include <QtCore/QList>
#include <QtCore/QPointF>
#include <QtCore/QString>

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
        /**
         * @brief Create invalid coordinates.
         */
        MapCoordinates();

        /**
         * @brief Copy a coordinates.
         *
         * @param other The coordinates to copy.
         */
        MapCoordinates(const MapCoordinates& other);

        /**
         * @brief Create coordinates from integer abscissa and ordinate.
         *
         * @param x Abscissa
         * @param y Ordinate
         */
        MapCoordinates(const int x, const int y);

        /**
         * @brief Create coordinates from real abscissa and ordinate.
         *
         * Note that real coordinates should only be used for dynamic elements.
         *
         * @param x Abscissa
         * @param y Ordinate
         */
        MapCoordinates(const qreal x, const qreal y);

        /**
         * @brief Assign the other coordinates to this one.
         *
         * @param other The coordinates to copy.
         */
        void operator =(const MapCoordinates& other);

        /**
         * @brief Indicate if the two coordinates are equal.
         *
         * @param other Other coordinates to compare to.
         */
        bool operator ==(const MapCoordinates& other) const;

        /**
         * @brief Indicate if the two coordinates are different.
         *
         * @param other Other coordinates to compare to.
         */
        bool operator !=(const MapCoordinates& other) const;

        /**
         * @brief Indicate if the coordinates are valid.
         *
         * This does not mean tat the coordinates are valid on the map. This depends on the map and should therefore be check via Map::isValidCoordinates().
         */
        bool isValid() const;

        /**
         * @brief Get the abscissa of the coordinates.
         */
        qreal getX() const;

        /**
         * @brief Get the ordinate of the coordinates.
         */
        qreal getY() const;

        /**
         * @brief Indicate if the coordinates are rounded.
         */
        bool isRounded() const;

        /**
         * @brief Change the abscissa of the coordinates.
         *
         * @param x The new abscissa.
         */
        void setX(const qreal x);

        /**
         * @brief Change the ordinate of the coordinates.
         *
         * @param y The new ordinate.
         */
        void setY(const qreal y);

        /**
         * @brief Get the coordinates in the immediate north.
         *
         * @note If coordinates are real, the decimal part is kept.
         * @return New coordinates.
         */
        MapCoordinates getNorth() const;

        /**
         * @brief Get the coordinates in the immediate south.
         *
         * @note If coordinates are real, the decimal part is kept.
         * @return New coordinates.
         */
        MapCoordinates getSouth() const;

        /**
         * @brief Get the coordinates in the immediate east.
         *
         * @note If coordinates are real, the decimal part is kept.
         * @return New coordinates.
         */
        MapCoordinates getEast() const;

        /**
         * @brief Get the coordinates in the immediate west.
         *
         * @note If coordinates are real, the decimal part is kept.
         * @return New coordinates.
         */
        MapCoordinates getWest() const;

        /**
         * @brief Get the coordinates in the immediate top.
         *
         * @note If coordinates are real, the decimal part is kept.
         * @return New coordinates.
         */
        MapCoordinates getTop() const;

        /**
         * @brief Get the coordinates in the immediate right.
         *
         * @note If coordinates are real, the decimal part is kept.
         * @return New coordinates.
         */
        MapCoordinates getRight() const;

        /**
         * @brief Get the coordinates in the immediate bottom.
         *
         * @note If coordinates are real, the decimal part is kept.
         * @return New coordinates.
         */
        MapCoordinates getBottom() const;

        /**
         * @brief Get the coordinates in the immediate left.
         *
         * @note If coordinates are real, the decimal part is kept.
         * @return New coordinates.
         */
        MapCoordinates getLeft() const;

        /**
         * @brief Get the integer coordinates corresponding to the coordinates.
         *
         * @return New coordinates.
         */
        MapCoordinates getRounded() const;

        /**
         * @brief Get the two rounded coordinates nearest the current coordinates.
         *
         * If the current coordinates are rounded, then it will only return a list containing those coordinates.
         * However, if the current coordinates are not rounded, they are considered has between two rounded coordinates.
         * We then return the list of those two coordinates.
         *
         * @return A list of one or two coordinates.
         */
        QList<MapCoordinates> getClosestRounded() const;

        /**
         * @brief Get Manhattan distance between two coordinates.
         *
         * @param other The coordinates to use to calculate the distance from.
         * @return The Manhattan distance.
         */
        qreal getManhattanDistanceTo(const MapCoordinates& other) const;

        /**
         * @brief Get Chebyshev distance between two coordinates.
         *
         * @param other The coordinates to use to calculate the distance from.
         * @return The Chebyshev distance.
         */
        qreal getChebyshevDistanceTo(const MapCoordinates& other) const;

        /**
         * @brief Get straight distance between two coordinates.
         * @param other The coordinates to use to calculate the distance from.
         * @return The straight distance.
         */
        qreal getStraightDistanceTo(const MapCoordinates& other) const;

        // DEBUG //
        QString toString() const;
};

#endif // MAPCOORDINATES_HPP
