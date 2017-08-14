#ifndef TARGETEDWALKERGENERATOR_HPP
#define TARGETEDWALKERGENERATOR_HPP

#include "engine/element/dynamic/TargetedWalker.hpp"
#include "engine/element/static/behavior/AbstractWalkerBehavior.hpp"
#include "engine/map/searchEngine/SearchEngine.hpp"

class TargetedWalkerGenerator : public AbstractWalkerBehavior
{
        Q_OBJECT

    private:
        const SearchEngine* searchEngine;
        StaticSearchCriteria targetSearchCriteria;
        const DynamicElementInformation* walkerConf;
        const int generationInterval;
        const int maxWalkers;
        qreal generationSpeedRatio;
        bool needToSetupNextGenerationDate;
        CycleDate nextGenerationDate;
        QList<QPointer<TargetedWalker>> walkers;

    public:
        TargetedWalkerGenerator(
            AbstractProcessableStaticMapElement* issuer,
            const SearchEngine* searchEngine,
            const StaticSearchCriteria* targetSearchCriteria,
            const DynamicElementInformation* walkerConf,
            const int generationInterval,
            const int maxWalkers = 1
        );

        /**
         * @brief Indicate if the walker belongs to this walker generator.
         * @param walker
         */
        bool contains(const TargetedWalker* walker) const;

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
        void setupNextGenerationDate(const CycleDate& currentDate);

        void generate(AbstractProcessableStaticMapElement* target);
};

#endif // TARGETEDWALKERGENERATOR_HPP
