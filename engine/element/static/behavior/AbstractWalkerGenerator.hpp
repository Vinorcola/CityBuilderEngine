#ifndef ABSTRACTWALKERGENERATOR_HPP
#define ABSTRACTWALKERGENERATOR_HPP

#include <functional>
#include <QtCore/QList>
#include <QtCore/QPointer>

#include "engine/element/dynamic/TargetedWalker.hpp"
#include "engine/element/static/behavior/AbstractStaticElementBehavior.hpp"
#include "engine/processing/CycleDate.hpp"

class AbstractDynamicMapElement;
class AbstractProcessableStaticMapElement;
class DynamicElementInformation;

class AbstractWalkerGenerator : public AbstractStaticElementBehavior
{
        Q_OBJECT

    protected:
        AbstractProcessableStaticMapElement* issuer;
        const DynamicElementInformation* walkerConf;
        const int generationInterval;
        const int maxWalkers;
        qreal generationSpeedRatio;
        bool needToSetupNextGenerationDate;
        CycleDate nextGenerationDate;
        QList<QPointer<TargetedWalker>> walkers;

    public:
        AbstractWalkerGenerator(
            AbstractProcessableStaticMapElement* issuer,
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
        virtual void clean();

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

        virtual void process(const CycleDate& date) override;

        virtual bool processInteraction(const CycleDate& date, AbstractDynamicMapElement* actor) override;

    protected:
        virtual bool canSetupNextGenerationDate(const CycleDate& currentDate) const;

        void setupNextGenerationDate(const CycleDate& currentDate);

        virtual void generate();

    signals:
        void requestDynamicElementCreation(
            const DynamicElementInformation* elementConf,
            AbstractProcessableStaticMapElement* issuer,
            std::function<void(AbstractDynamicMapElement*)> afterCreation
        );

        void requestDynamicElementDestruction(
            AbstractDynamicMapElement* element,
            std::function<void()> afterDestruction
        );
};

#endif // ABSTRACTWALKERGENERATOR_HPP
