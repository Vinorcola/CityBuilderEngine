#ifndef BEHAVIORFACTORY_HPP
#define BEHAVIORFACTORY_HPP

#include <QtCore/QObject>
#include <QtCore/QList>

class AbstractStaticElementBehavior;
class BehaviorInformation;
class Map;
class ProcessableBuilding;
class SearchEngine;

/**
 * @brief The behavior factory.
 *
 * Instanciate a new behavior based on the given behavior configuration provided.
 */
class BehaviorFactory : public QObject
{
        Q_OBJECT

    private:
        const Map* map;
        const SearchEngine* searchEngine;

    public:
        BehaviorFactory(QObject* parent, const Map* map, const SearchEngine* searchEngine);

        AbstractStaticElementBehavior* generate(ProcessableBuilding* issuer, const BehaviorInformation* conf) const;
};

#endif // BEHAVIORFACTORY_HPP
