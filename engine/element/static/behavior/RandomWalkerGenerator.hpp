#ifndef RANDOMWALKERGENERATOR_HPP
#define RANDOMWALKERGENERATOR_HPP

#include "engine/element/dynamic/RandomWalker.hpp"
#include "engine/element/static/behavior/AbstractStaticElementBehavior.hpp"
#include "global/conf/DynamicElementInformation.hpp"

class RandomWalkerGenerator : public AbstractStaticElementBehavior
{
        Q_OBJECT

    private:
        const DynamicElementInformation* walkerConf;
        const int generationInterval;
        const int maxWalkers;
        qreal generationSpeedRatio;
        bool needToSetupNextGenerationDate;
        CycleDate nextGenerationDate;
        QList<QPointer<RandomWalker>> walkers;

    public:
        RandomWalkerGenerator(
            QObject* parent,
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
        void clean();

        /**
         * @brief Change the generation speed ratio.
         *
         * The current date is needed in order to calculate the next generation date according to the new generation
         * speed ratio. Note that a ratio of 0 will reset the next generation date.
         *
         * @param ratio
         * @param currentDate
         */
        void setGenerationSpeedRatio(qreal ratio, const CycleDate& currentDate);

        virtual void process(const CycleDate &date) override;

        virtual bool processInteraction(const CycleDate& date, AbstractDynamicMapElement* actor) override;

    protected:
        void setupNextGenerationDate(const CycleDate& currentDate);

        void generate();

    signals:
        void requestDynamicElementCreation(
            const DynamicElementInformation* elementConf,
            std::function<void(AbstractDynamicMapElement*)> afterCreation
        );

        void requestDynamicElementDestruction(
            AbstractDynamicMapElement* element,
            std::function<void()> afterDestruction
        );
};

#endif // RANDOMWALKERGENERATOR_HPP
