#ifndef CONDITIONALRANDOMWALKERGENERATOR_HPP
#define CONDITIONALRANDOMWALKERGENERATOR_HPP

#include "engine/element/static/behavior/RandomWalkerGenerator.hpp"

class ConditionalRandomWalkerGenerator : public RandomWalkerGenerator
{
        Q_OBJECT

    private:
        const DynamicElementInformation* dependencyWalkerConf;
        const int activityInterval;
        CycleDate canGenarateWalkerUntilDate;

    public:
        ConditionalRandomWalkerGenerator(
            QObject* parent,
            const DynamicElementInformation* walkerConf,
            const DynamicElementInformation* dependencyWalkerConf,
            const int generationInterval,
            const int maxWalkers = 1
        );

        virtual void process(const CycleDate &date) override;

        virtual bool processInteraction(const CycleDate& date, AbstractDynamicMapElement* actor) override;
};

#endif // CONDITIONALRANDOMWALKERGENERATOR_HPP
