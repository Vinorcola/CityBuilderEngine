#ifndef ABSTRACTBEHAVIOR_HPP
#define ABSTRACTBEHAVIOR_HPP

#include <QtCore/QObject>

#include "src/engine/processing/AbstractProcessable.hpp"

class Character;
class CycleDate;

/**
 * @brief The base class for buildings' behaviors.
 */
class AbstractBehavior : public QObject, public AbstractProcessable
{
        Q_OBJECT

    public:
        AbstractBehavior(QObject* parent);

        virtual bool processInteraction(const CycleDate& date, Character* actor) = 0;
};

#endif // ABSTRACTBEHAVIOR_HPP
