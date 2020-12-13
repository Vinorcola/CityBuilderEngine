#ifndef CHARACTERVIEW_HPP
#define CHARACTERVIEW_HPP

#include "src/defines.hpp"

class Character;
class CharacterImage;
class ImageLibrary;
class DynamicElement;
class MapCoordinates;
class Positioning;
class TileView;
class TileLocatorInterface;
struct CharacterState;

/**
 * @brief Handles the graphical representation of a character.
 *
 * It keeps a weak pointer to the engine data of the character and knows all the logic needed to update the graphics
 * according to those data.
 */
class CharacterView
{
    private:
        const Positioning& positioning;
        const TileLocatorInterface& tileLocator;
        TileView* currentTile;
        const CharacterImage& image;
        owner<DynamicElement*> graphicElement;
        int currentStateVersion;
        int animationIndex;

    public:
        CharacterView(
            const Positioning& positioning,
            const TileLocatorInterface& tileLocator,
            const ImageLibrary& imageLibrary,
            const CharacterState& state
        );
        ~CharacterView();

        void update(const CharacterState& state);
        void destroy();

    private:
        void move(const MapCoordinates& newLocation);
        void advanceAnimation();
};

#endif // CHARACTERVIEW_HPP
