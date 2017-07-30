#ifndef DYNAMICELEMENT_HPP
#define DYNAMICELEMENT_HPP

#include <QGraphicsPixmapItem>

#include "engine/element/dynamic/AbstractDynamicMapElement.hpp"

class DynamicElement : public QGraphicsPixmapItem
{
    private:
        const QSizeF& baseTileSize;
        QWeakPointer<AbstractDynamicMapElement> element;

    public:
        DynamicElement(const QSizeF& baseTileSize, const QWeakPointer<AbstractDynamicMapElement>& element, const QPixmap& elementImage);

        /**
         * @brief Indicae if the logical element linked to this graphical element still exists.
         */
        bool stillExists();

        MapCoordinates getCoordinates() const;

        void refresh();
};

#endif // DYNAMICELEMENT_HPP
