#ifndef ABSTRACTCHARACTER_HPP
#define ABSTRACTCHARACTER_HPP

#include "engine/element/AbstractDynamicMapElement.hpp"

/**
 * @brief The base class for characters.
 *
 * @note Not sure this class is usefull... Maybe AbstractDynamicMapElement is enough.
 */
class AbstractCharacter : public AbstractDynamicMapElement
{
    public:
        AbstractCharacter(const MapCoordinates& initialLocation);
};

#endif // ABSTRACTCHARACTER_HPP
