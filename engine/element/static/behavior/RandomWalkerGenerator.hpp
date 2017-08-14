#ifndef RANDOMWALKERGENERATOR_HPP
#define RANDOMWALKERGENERATOR_HPP

#include <QtCore/QList>
#include <QtCore/QPointer>

#include "engine/element/dynamic/RandomWalker.hpp"
#include "engine/element/static/behavior/AbstractWalkerBehavior.hpp"
#include "engine/processing/CycleDate.hpp"

class AbstractDynamicMapElement;
class AbstractProcessableStaticMapElement;
class DynamicElementInformation;

class RandomWalkerGenerator : public AbstractWalkerBehavior
{
        Q_OBJECT

    protected:
        const DynamicElementInformation* walkerConf;
        const int generationInterval;
        const int maxWalkers;
        qreal generationSpeedRatio;
        bool needToSetupNextGenerationDate;
        CycleDate nextGenerationDate;
        QList<QPointer<RandomWalker>> walkers;

    public:
        RandomWalkerGenerator(
            AbstractProcessableStaticMapElement* issuer,
            const DynamicElementInformation* walkerConf,
            const int generationInterval,
            const int maxWalkers = 1
        );

        /**
         * @brief Indicate if the walker belongs to this walker generator.
         * @param walker
         */
        bool contains(const RandomWalker* walker) const;

        /**
         * @brief Clean the list of walkers by removing deleted walkers.
         */
        virtual void clean() override;

        /**
         * @brief Change the generation speed ratio.
         *
         * The current date is needed in order to calculate the next generation date according to the new generation
         * speed ratio. Note that a ratio of 0 will reset the next generation date.
         *
         * @param ratio
         * @param currentDate
         */
        virtual void setActivitySpeedRatio(qreal ratio, const CycleDate& currentDate) override;

        virtual void process(const CycleDate &date) override;

        virtual bool processInteraction(const CycleDate& date, AbstractDynamicMapElement* actor) override;

    protected:
        virtual bool canGenerate(const CycleDate& currentDate) const;

        void setupNextGenerationDate(const CycleDate& currentDate);

        void generate();
};

#endif // RANDOMWALKERGENERATOR_HPP
