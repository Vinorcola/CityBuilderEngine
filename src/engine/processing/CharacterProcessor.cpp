#include "CharacterProcessor.hpp"

#include "src/engine/element/dynamic/character/Character.hpp"



CharacterProcessor::CharacterProcessor() :
    AbstractProcessable(),
    processableList(),
    waitingForRegistrationList(),
    waitingForUnregistrationList()
{

}



void CharacterProcessor::registerCharacter(Character& character)
{
    waitingForRegistrationList.append(character.getReference<Character>());
}



void CharacterProcessor::unregisterCharacter(Character& character)
{
    waitingForUnregistrationList.append(&character);
}



void CharacterProcessor::process(const CycleDate& date)
{
    // Process current processable list.
    for (auto processable : processableList) {
        if (processable.isValid()) {
            processable.get().process(date);
        }
    }

    // Process unregistration.
    processableList.cleanAllInvalids();
    while (!waitingForUnregistrationList.isEmpty()) {
        processableList.remove(*waitingForUnregistrationList.takeFirst());
    }

    // Process registration.
    waitingForRegistrationList.moveAllContentTo(processableList);
}
