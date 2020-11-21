#include "CharacterProcessor.hpp"

#include "src/engine/element/dynamic/character/Character.hpp"
#include "src/global/pointer/SmartPointerUtils.hpp"



CharacterProcessor::CharacterProcessor() :
    AbstractProcessable(),
    processableList(),
    waitingForRegistrationList(),
    waitingForUnregistrationList()
{

}



void CharacterProcessor::registerCharacter(const QSharedPointer<Character>& character)
{
    waitingForRegistrationList.append(character);
}



void CharacterProcessor::unregisterCharacter(const QSharedPointer<Character>& character)
{
    waitingForUnregistrationList.append(character.get());
}



void CharacterProcessor::process(const CycleDate& date)
{
    // Process current processable list.
    for (auto& processableRef : processableList) {
        auto processable(processableRef.toStrongRef());
        if (processable) {
            processable->process(date);
        }
    }

    // Process unregistration.
    cleanInvalids(processableList);
    while (!waitingForUnregistrationList.isEmpty()) {
        processableList.remove(waitingForUnregistrationList.takeFirst());
    }

    // Process registration.
    for (auto& newProcessable : waitingForRegistrationList) {
        newProcessable->init(date);
        processableList.insert(newProcessable.get(), newProcessable);
    }
    waitingForRegistrationList.clear();
}
