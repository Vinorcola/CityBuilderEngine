#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <QtCore/QObject>
#include <QtCore/QPointer>

#include "src/engine/element/dynamic/MotionHandler.hpp"
#include "src/engine/processing/AbstractProcessable.hpp"
#include "src/defines.hpp"

class CharacterInformation;
class CharacterManagerInterface;
class MapCoordinates;
class PathGeneratorInterface;
class ProcessableBuilding;

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
class Character : public QObject, public AbstractProcessable
{
        Q_OBJECT

    protected:
        CharacterManagerInterface& characterManager;///< A service for requiring the character destruction.
        const PathGeneratorInterface& pathGenerator;///< A service for generating paths.
        const CharacterInformation& conf;///< The character configuration.
        MotionHandler motionHandler;///< A helper that will handle the character's motion.
        QPointer<ProcessableBuilding> issuer;///< The issuer building.

    public:
        Character(
            QObject* parent,
            CharacterManagerInterface& characterManager,
            const PathGeneratorInterface& pathGenerator,
            const CharacterInformation& conf,
            ProcessableBuilding& issuer
        );

        bool isOfType(const CharacterInformation& conf) const;

        const CharacterInformation& getConf() const;

        const MapCoordinates& getCurrentLocation() const;

        optional<ProcessableBuilding*> getIssuer() const;

        /**
         * @brief Make the charater move.
         */
        virtual void process(const CycleDate& date) override;
};

#endif // CHARACTER_HPP
