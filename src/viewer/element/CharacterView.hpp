#ifndef CHARACTERVIEW_HPP
#define CHARACTERVIEW_HPP

#include "src/global/CharacterStatus.hpp"
#include "src/defines.hpp"

class Character;
class CharacterImage;
class DynamicElement;
class DynamicElementCoordinates;
class ImageLibrary;
class Positioning;
class TileLocatorInterface;
class TileView;
struct CharacterState;

/**
 * @brief Handles the graphical representation of a character.
 *
 * It keeps a weak pointer to the engine data of the character and knows all the logic needed to update the graphics
 * according to those data.
 */
class CharacterView
{
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
        void move(const DynamicElementCoordinates& newLocation);
        void advanceAnimation(CharacterStatus status);

    private:
        const Positioning& positioning;
        const TileLocatorInterface& tileLocator;
        TileView* currentTile;
        const CharacterImage& image;
        owner<DynamicElement*> graphicElement;
        int currentStateVersion;
        int animationIndex;
};

#endif // CHARACTERVIEW_HPP
