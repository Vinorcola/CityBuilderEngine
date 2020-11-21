#ifndef CHARACTERPROCESSOR_HPP
#define CHARACTERPROCESSOR_HPP

#include <QtCore/QList>
#include <QtCore/QSharedPointer>

#include "src/engine/processing/AbstractProcessable.hpp"

class Character;
class CycleDate;

/**
 * @brief A processor for all map's characters.
 */
class CharacterProcessor : public AbstractProcessable
{
    private:
        QHash<const Character*, QWeakPointer<Character>> processableList;
        QList<QSharedPointer<Character>> waitingForRegistrationList;
        QList<const Character*> waitingForUnregistrationList;

    public:
        CharacterProcessor();

        /**
         * @brief Register a character to be process each time cycle.
         */
        void registerCharacter(const QSharedPointer<Character>& character);

        /**
         * @brief Unregister a character from processor.
         */
        void unregisterCharacter(const QSharedPointer<Character>& character);

        virtual void process(const CycleDate& date) override;
};

#endif // CHARACTERPROCESSOR_HPP
