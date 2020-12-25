#include "CharacterStatus.hpp"

#include <QtCore/QString>

#include "src/exceptions/BadConfigurationException.hpp"



uint qHash(const CharacterStatus& status)
{
    return static_cast<uint>(status);
}



CharacterStatus resolveCharacterStatus(const QString& status)
{
    if (status == "dying")         return CharacterStatus::Dying;
    if (status == "fighting")      return CharacterStatus::Fighting;
    if (status == "walking")       return CharacterStatus::Walking;
    if (status == "walkingLoaded") return CharacterStatus::WalkingLoaded;
    if (status == "working")       return CharacterStatus::Working;

    throw BadConfigurationException("Unknown character status \"" + status + "\".");
}
