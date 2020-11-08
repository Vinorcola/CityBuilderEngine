#ifndef CHARACTERVIEW_HPP
#define CHARACTERVIEW_HPP

#include <QtCore/QSharedPointer>
#include <QtCore/QSizeF>
#include <QtCore/QWeakPointer>

#include "src/defines.hpp"

class Character;
class CharacterImage;
class ImageLibrary;
class DynamicElement;
class MapCoordinates;
class Positioning;
class Tile;
class TileLocatorInterface;

class CharacterView
{
    private:
        const Positioning& positioning;
        const TileLocatorInterface& tileLocator;
        QWeakPointer<const Character> engineData;
        Tile* currentTile;
        const CharacterImage& image;
        owner<DynamicElement*> graphicElement;
        int currentViewVersion;
        int animationIndex;

    public:
        CharacterView(
            const Positioning& positioning,
            const TileLocatorInterface& tileLocator,
            const ImageLibrary& imageLibrary,
            const QSharedPointer<const Character>& engineData
        );

        ~CharacterView();

        void updateFromEngineData();

        bool hasBeenDestroyed() const;

    private:
        void move(const MapCoordinates& newLocation);

        void advanceAnimation();

        void setDestroyed();
};

#endif // CHARACTERVIEW_HPP
