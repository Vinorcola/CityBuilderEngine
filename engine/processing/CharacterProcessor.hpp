#ifndef CHARACTERPROCESSOR_HPP
#define CHARACTERPROCESSOR_HPP

#include <QtCore/QLinkedList>
#include <QtCore/QList>
#include <QtCore/QObject>
#include <QtCore/QPointer>

#include "engine/processing/AbstractProcessable.hpp"

class Character;

/**
 * @brief A processor for all map's characters.
 */
class CharacterProcessor : public QObject, public AbstractProcessable
{
        Q_OBJECT

    private:
        QLinkedList<QPointer<Character>> processableList;
        QList<QPointer<Character>> waitingForRegistrationList;
        QList<Character*> waitingForUnregistrationList;

    public:
        explicit CharacterProcessor(QObject* parent);

        /**
         * @brief Register a character to be process each time cycle.
         */
        void registerCharacter(Character* character);

        /**
         * @brief Unregister a character from processor.
         */
        void unregisterCharacter(Character* character);

        virtual void process(const CycleDate& date);
};

#endif // CHARACTERPROCESSOR_HPP
