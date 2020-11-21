#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "src/engine/element/dynamic/MotionHandler.hpp"
#include "src/engine/processing/AbstractProcessable.hpp"
#include "src/defines.hpp"

class AbstractProcessableBuilding;
class CharacterInformation;
class CharacterManagerInterface;
class MapCoordinates;
class PathGeneratorInterface;
struct CharacterState;

/**
 * @brief A character on the map.
 *
 * A character is a dynamic element that can move (e.g. change its coordinates through time). It do not have any size,
 * so it does not cover any area. It is just represented by some coordinates and should be perceived as mathematical
 * points.
 *
 * Characters are always issued from a building. This building (the `issuer`) does not strictly own the character:
 * all the characters belong to the map. Furthermore, a charater can be kept alive even if the issuer has been
 * destroyed.
 *
 * If a character is granted wandering credits, it will use them to wander around (see MotionHandler for more details).
 * Otherwise, the character won't move until a target is assigned to it.
 */
class Character : public AbstractProcessable
{
    protected:
        CharacterManagerInterface& characterManager; ///< A service for requiring the character destruction.
        const PathGeneratorInterface& pathGenerator; ///< A service for generating paths.
        const CharacterInformation& conf; ///< The character configuration.
        MotionHandler motionHandler; ///< A helper that will handle the character's motion.
        QWeakPointer<AbstractProcessableBuilding> issuer; ///< The issuer building.
        int stateVersion; ///< We use an int for the versionning of the view. Note that an overflow is not dramatic since we always compare versions using equality.

    public:
        Character(
            CharacterManagerInterface& characterManager,
            const PathGeneratorInterface& pathGenerator,
            const CharacterInformation& conf,
            const QSharedPointer<AbstractProcessableBuilding>& issuer
        );

        bool isOfType(const CharacterInformation& conf) const;
        const QWeakPointer<AbstractProcessableBuilding>& getIssuer() const;

        CharacterState getCurrentState() const;

        /**
         * @brief Make the charater move.
         */
        virtual void process(const CycleDate& date) override;

    protected:
        void notifyViewDataChange();
};

#endif // CHARACTER_HPP
