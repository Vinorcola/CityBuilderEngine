#ifndef CHARACTERPROCESSOR_HPP
#define CHARACTERPROCESSOR_HPP

#include <QtCore/QList>

#include "src/engine/element/dynamic/character/Character.hpp"
#include "src/engine/processing/AbstractProcessable.hpp"
#include "src/global/reference/collection/ReferenceCollection.hpp"

class Character;
class CycleDate;

/**
 * @brief A processor for all map's characters.
 */
class CharacterProcessor : public AbstractProcessable
{
    private:
        ReferenceCollection<Character> processableList;
        ReferenceCollection<Character> waitingForRegistrationList;
        QList<Character*> waitingForUnregistrationList;

    public:
        CharacterProcessor();

        /**
         * @brief Register a character to be process each time cycle.
         */
        void registerCharacter(Character& character);

        /**
         * @brief Unregister a character from processor.
         */
        void unregisterCharacter(Character& character);

        virtual void process(const CycleDate& date) override;
};

#endif // CHARACTERPROCESSOR_HPP
