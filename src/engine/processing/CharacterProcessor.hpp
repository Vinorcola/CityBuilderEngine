#ifndef CHARACTERPROCESSOR_HPP
#define CHARACTERPROCESSOR_HPP

#include <QtCore/QList>
#include <QtCore/QSharedPointer>

#include "src/engine/processing/AbstractProcessable.hpp"

class CycleDate;

/**
 * @brief A processor for all map's characters.
 *
 * @deprecated Will be deleted in favor of DynamicElementRegistry.
 */
class CharacterProcessor : public AbstractProcessable
{
    private:
        QHash<const AbstractProcessable*, QWeakPointer<AbstractProcessable>> processableList;
        QList<QSharedPointer<AbstractProcessable>> waitingForRegistrationList;
        QList<const AbstractProcessable*> waitingForUnregistrationList;

    public:
        CharacterProcessor();

        /**
         * @brief Register a character to be process each time cycle.
         */
        void registerCharacter(const QSharedPointer<AbstractProcessable>& character);

        /**
         * @brief Unregister a character from processor.
         */
        void unregisterCharacter(const QSharedPointer<AbstractProcessable>& character);

        virtual void process(const CycleDate& date) override;
};

#endif // CHARACTERPROCESSOR_HPP
