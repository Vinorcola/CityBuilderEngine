#ifndef QUEUEDWALKERGENERATOR_HPP
#define QUEUEDWALKERGENERATOR_HPP

#include <functional>
#include <QtCore/QList>

#include "engine/element/static/behavior/AbstractBehavior.hpp"
#include "engine/processing/CycleDate.hpp"

class Character;
class CharacterInformation;
class ProcessableBuilding;

/**
 * @brief A queued walker generator.
 *
 * This walker generator does not inherit from AbstractWalkerGenerator because it's behavior is quite different. Walkers
 * are not generated in a result of an activity. They are rather generated on external request. External requests are
 * queued and treated one at the time. The laps between 2 requests is set randomly using a min laps and a max laps.
 *
 * This behavior is mainly used by CityEntryPoint.
 */
class QueuedWalkerGenerator : public AbstractBehavior
{
        Q_OBJECT

    private:
        ProcessableBuilding* issuer;
        const CharacterInformation* walkerConf;
        const int minGenerationInterval;
        const int maxGenerationInterval;
        CycleDate nextWalkerGenerationDate;
        QList<std::function<void(Character*)>> walkerRequestQueue;

    public:
        QueuedWalkerGenerator(
            ProcessableBuilding* issuer,
            const CharacterInformation* walkerConf,
            const int minGenerationInterval,
            const int maxGenerationInterval
        );

        const CharacterInformation* getWalkerConf() const;

        virtual void process(const CycleDate& date) override;

        virtual bool processInteraction(const CycleDate& date, Character* actor) override;

        void registerWalkerRequest(std::function<void(Character*)> onWalkerCreation);

    protected:
        void setupNextWalkerGenerationDate(const CycleDate& currentDate);

    signals:
        void requestDynamicElementCreation(
            const CharacterInformation* conf,
            ProcessableBuilding* issuer,
            std::function<void(Character*)> afterCreation
        );
};

#endif // QUEUEDWALKERGENERATOR_HPP
