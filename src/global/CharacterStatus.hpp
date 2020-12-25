#ifndef CHARACTERSTATUS_HPP
#define CHARACTERSTATUS_HPP

#include <QtCore/QtGlobal>

/**
 * An enumeration for available character statuses.
 */
enum class CharacterStatus {
    Dying,
    Fighting,
    Walking,
    WalkingLoaded,
    Working,
};

uint qHash(const CharacterStatus& status);

CharacterStatus resolveCharacterStatus(const QString& status);

#endif // CHARACTERSTATUS_HPP
