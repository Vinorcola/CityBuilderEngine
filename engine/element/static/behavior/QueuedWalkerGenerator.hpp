#ifndef QUEUEDWALKERGENERATOR_HPP
#define QUEUEDWALKERGENERATOR_HPP

#include <functional>
#include <QtCore/QList>

#include "engine/element/static/behavior/AbstractStaticElementBehavior.hpp"
#include "engine/processing/CycleDate.hpp"

class AbstractDynamicMapElement;
class AbstractProcessableStaticMapElement;
class DynamicElementInformation;
class TargetedWalker;

/**
 * @brief A queued walker generator.
 *
 * This walker generator does not inherit from AbstractWalkerGenerator because it's behavior is quite different. Walkers
 * are not generated in a result of an activity. They are rather generated on external request. External requests are
 * queued and treated one at the time. The laps between 2 requests is set randomly using a min laps and a max laps.
 */
class QueuedWalkerGenerator : public AbstractStaticElementBehavior
{
        Q_OBJECT

    private:
        AbstractProcessableStaticMapElement* issuer;
        const DynamicElementInformation* walkerConf;
        const int minGenerationInterval;
        const int maxGenerationInterval;
        CycleDate nextWalkerGenerationDate;
        QList<std::function<void(AbstractDynamicMapElement*)>> walkerRequestQueue;

    public:
        QueuedWalkerGenerator(
            AbstractProcessableStaticMapElement* issuer,
            const DynamicElementInformation* walkerConf,
            const int minGenerationInterval,
            const int maxGenerationInterval
        );

        const DynamicElementInformation* getWalkerConf() const;

        virtual void process(const CycleDate& date) override;

        virtual bool processInteraction(const CycleDate& date, AbstractDynamicMapElement* actor) override;

        void registerWalkerRequest(std::function<void(AbstractDynamicMapElement*)> onWalkerCreation);

    protected:
        void setupNextWalkerGenerationDate(const CycleDate& currentDate);

    signals:
        void requestDynamicElementCreation(
            const DynamicElementInformation* elementConf,
            AbstractProcessableStaticMapElement* issuer,
            std::function<void(AbstractDynamicMapElement*)> afterCreation
        );
};

#endif // QUEUEDWALKERGENERATOR_HPP
